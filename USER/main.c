#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
#include "flash.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "gt911.h"
#include "protocol.h"
#include "can.h" 
#include "stm32f4xx_hal.h"      // 为 CanRxMsgTypeDef 等
#include "main.h"
#include "rtc.h"
#include "uart.h"


/// @brief external variables
extern volatile uint16_t Currenttargeweight;
extern volatile uint8_t dataIsReady;
extern uint8_t rFrameBuf[FRAME_MAX_LEN];
extern uint8_t recivedCount;

/// @brief static global variables
static uint8_t buf[FRAME_MAX_LEN];
static struct Protocol c;
static const char version[12] = "MRC_V1.0.0";

void vLvglTaskFunction( void * pvParameters );
void thread_serial(void *pvParameters);

struct GrindRealData GrindDataStr;
struct GrindData GrindDatarx;//GrindData
TaskHandle_t xLvglTaskHandle = NULL;  
TaskHandle_t xFlashTaskHandle = NULL;
TaskHandle_t xSerialTaskHandle = NULL; 

lv_ui guider_ui;

bool isGrindMode = MODE_TIME;

CanMsg can_msg = {0};

// 接收完成：从 HAL 的 pRxMsg 读取数据，转交给 CAN_UserRxCb，然后重新使能接收
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan_if)
{
    CanRxMsgTypeDef *r = hcan_if->pRxMsg;

    uint8_t i = 0;

    can_msg.rx_dlen = r->DLC;

    for (i = 0; i < r->DLC && i < 8; i++) 
        can_msg.rx_data[i] = r->Data[i];

    for (; i < 8; i++) 
        can_msg.rx_data[i] = 0x00;

#ifdef CAN_Id_Extended
    if (r->IDE == CAN_Id_Extended) {
        can_msg.rx_efid = r->ExtId;
        printf("11111");
        can_msg.data_is_ready = 1;
    } 
#else
    // 如果你的 HAL 没有 CAN_Id_Extended 宏，使用常见数值判断：0x04 表示扩展（老 HAL 习惯）
    if (r->IDE == 0x04U) {
        is_ext = 1; id = r->ExtId;
    } else {
        is_ext = 0; id = r->StdId;
    }
#endif
    // 转给我们封装的用户回调（由用户覆盖）
    //CAN_UserRxCb(is_ext, id, r->DLC, data);

    // 重新使能接收（legacy HAL 的 Receive_IT 是一次性的）
    HAL_CAN_Receive_IT(hcan_if, CAN_FIFO0);
}

// 发送完成回调：通知用户
void HAL_CAN_TxCpltCallback(CAN_HandleTypeDef *hcan_if)
{
    (void)hcan_if;
    CAN_UserTxCb();
}

// 错误回调：转发或记录错误码。你可以在这里打印 hcan_if->ErrorCode
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan_if)
{
    // 用户可覆盖 HAL_CAN_ErrorCallback 或实现 CAN_UserXXX 来打印错误
    // 例如：Debug_Printf("CAN err 0x%08lX\n", hcan_if->ErrorCode);
}

void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; 
    DWT->CYCCNT = 0;                                
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;           
}

/// 32K offset
#define APP_FLASH_OFFSET 0x8000
int main(void)
{ 
    
    SCB->VTOR = FLASH_BASE | APP_FLASH_OFFSET;
	DWT_Init();
	BaseType_t xReturned;
	HAL_Init();      
    
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); 
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0); 
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
	STM32_Clock_Init(336,25,2,7);  	

	delay_init(168);               
	LED_Init();					
	//TIM2_Init();	
	//KEY_Init();
    uart6_init(); 

    ISL1208_Init();

    // ISL1208_Time_t current_time;
    // ISL1208_Time_t time_read;
    // // // 2. 设置时间
    // current_time.seconds = 00;
    // current_time.minutes = 57;
    // current_time.hours = 11;    // 14:45:30
    // current_time.date = 6;
    // current_time.month = 3;
    // current_time.year = 26;     // 2026年
    // current_time.day = 5;       // 星期天
    // current_time.format_12h = 0; // 24小时制
    
    // ISL1208_SetTime(&current_time);

    // 3. 读取时间
    
    printf("App is running.Version:%s Compiled on %s %s\n",version,__DATE__,__TIME__);

    uart4_init();
    gt911_init();

    flashDataInit();
    
    CAN_Init_IT(500);
    CAN_ConfigFilterAcceptAll();
    CAN_StartReceive_IT();
    
	xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,2,&xLvglTaskHandle);
    xTaskCreate(thread_serial, "thread_serial", 1024, NULL, 3, &xSerialTaskHandle);
	vTaskStartScheduler();  


    while (1)                                            
    {           
	}
}


void thread_serial(void *pvParameters)
{
    int len = 0;
    int timeover = 0;
    GrindDataStr.data.mode = MODE_TIME;
    GrindDataStr.data.target = 3000; ///ms
    GrindDataStr.data.cmd_number = 0;
    GrindDataStr.data.cmd_state = CMD_STATE_IDLE;
    GrindDataStr.data.cmd = CMDTYPE_GRIND;
    uint8_t laststate = 0;

    static TickType_t lastUpdateTime = 0;
    const TickType_t updateTimePeriod = pdMS_TO_TICKS(5000); // 30秒周期
    int time = 0;
    ISL1208_Time_t time_read;
    bool isfillwater = false;
    // //读取时间
    // ISL1208_GetTime(&time_read);

    while (1){

   // 开机5s后补一次水
        TickType_t currentTime = xTaskGetTickCount();
        if (currentTime - lastUpdateTime >= updateTimePeriod && time < 2 ) {           
            GrindDataStr.data.cmd = CMDTYPE_SYSTEM_FILL_WATER;
            time++;
        } 
        
        if (GrindDataStr.data.cmd == CMDTYPE_GRIND){

        } else if (GrindDataStr.data.cmd == CMDTYPE_SYSTEM_FILL_WATER){
            len = setFillwater(buf,&GrindDataStr.data);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
            sendData(buf, len);
        } else if (GrindDataStr.data.cmd == CMDTYPE_MAKE_STEAM){
            len = setdosteam(buf, &GrindDataStr.data);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
            sendData(buf, len);
        } else if (GrindDataStr.data.cmd == CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB ){
            len = setcancel(buf, &GrindDataStr.data);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
            sendData(buf, len);
        }
        
        timeover = 0;
        while (!dataIsReady && timeover < 20) {
            timeover++;
            vTaskDelay(pdMS_TO_TICKS(1));
        }
        #if 1
        if (timeover >= 20) {
            // printf("timeover line = %d\r\n", __LINE__);
            uint32_t error_code;// = huart->ErrorCode;
            uint32_t sr_register = UART4->SR;  // 直接读取状态寄存器
            
            // 打印错误信息（如果可以使用printf）
            // printf("UART4 Error!  SR: 0x%04lX\r\n", sr_register);
        }
        #endif
        if (dataIsReady){
            dataIsReady = 0;  
            getProtocol(rFrameBuf,&c);
            if (c.frame.cmd == CMDTYPE_SYSTEM_FILL_WATER){
            
            } 
            //     GrindDatarx.mode = c.frame.mode;
            //     GrindDatarx.target = c.frame.target;
            //     GrindDatarx.cmd_state = c.frame.cmd_state;
            //     GrindDatarx.cmd_number = c.frame.cmd_number;                        
            // if (GrindDataStr.data.cmd == CMDTYPE_GRIND){
            //     if (c.frame.cmd_state == CMD_STATE_EXECUTING){
            //         lv_obj_clear_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN); 
            //         lv_obj_add_flag(guider_ui.screen_btn_11, LV_OBJ_FLAG_HIDDEN);
            //         lv_obj_add_flag(guider_ui.screen_btn_12, LV_OBJ_FLAG_HIDDEN);

            //         char dataStr[20];  
                    
            //         if(GrindDataStr.data.mode == MODE_TIME){
            //             sprintf(dataStr, "%.1f", c.frame.target/1000.0f);
            //             lv_label_set_text(guider_ui.screen_label_8, dataStr); 
            //             lv_label_set_text(guider_ui.screen_label_9, "s"); 
            //         } else if(GrindDataStr.data.mode == MODE_WEIGHT){
            //             sprintf(dataStr, "%.1f", c.frame.target/10.0f);
            //             lv_label_set_text(guider_ui.screen_label_8, dataStr); 
            //             lv_label_set_text(guider_ui.screen_label_9, "g");
            //         }

            //     } else if (c.frame.cmd_state == CMD_STATE_PAUSE){
                    
            //     } else if (c.frame.cmd_state == CMD_STATE_SUCCESS) {
            //         lv_obj_clear_flag(guider_ui.screen_btn_11, LV_OBJ_FLAG_HIDDEN);
            //         lv_obj_clear_flag(guider_ui.screen_btn_12, LV_OBJ_FLAG_HIDDEN);
            //         // char time_str[10]; 
            //         // sprintf(time_str, "%.1f", GrindDataStr.data.target/1000.0f);
            //         // lv_label_set_text(guider_ui.screen_label_8, time_str); 

            //         if(laststate == CMD_STATE_EXECUTING)
            //         vTaskDelay(pdMS_TO_TICKS(2000));  // 延迟2000毫秒（2秒）
            //         lv_obj_add_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);          
            //     } 
            //     laststate = c.frame.cmd_state;  
            // } 

        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vLvglTaskFunction(void *pvParameters) {
    printf("LVGL task is running. \r\n");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(5); 

    nv3401_gpio_init();
    nv3401_lcd_init();

    lv_init();
	lv_port_disp_init();  
	lv_port_indev_init();  

	setup_ui(&guider_ui);
	events_init(&guider_ui);
    // images_init(&guider_ui);

    ISL1208_Time_t time_read;
    ISL1208_GetTime(&time_read);
    // update_time_display(&time_read);
    while (1) {

        static TickType_t xLastTickCount = 0;
        TickType_t xCurrentTickCount = xTaskGetTickCount();
        uint32_t elapsed_ticks = xCurrentTickCount - xLastTickCount;
        xLastTickCount = xCurrentTickCount;

        lv_tick_inc(elapsed_ticks * portTICK_PERIOD_MS); 

        lv_task_handler();

        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}


