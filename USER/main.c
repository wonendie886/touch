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

volatile CanMsg can_msg = {0};
// uint16_t can_rx_count = 0;
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
        // can_rx_count++;
        // printf("ide %d\r\n",can_rx_count);
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
    
	xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
    xTaskCreate(thread_serial, "thread_serial", 1024, NULL, 2, &xSerialTaskHandle);
	vTaskStartScheduler();  


    while (1)                                            
    {           
	}
}

extern volatile uint16_t volume;
float blocktemp = 0;
float brewtemp = 0;
volatile uint8_t coffee_run_flag = 0;
extern uint8_t teasetflag ;
extern uint8_t teaflag ;
bool startflag;
extern uint8_t scheduleall;
void CoffeeVolumeProcess(void)
{
    static TickType_t lastTick = 0;
    static int schedule = 0;
    // 没启动则直接返回
    if(coffee_run_flag == 0)
    {
        return;
    }
    
    // 每1s减一次
    if(xTaskGetTickCount() - lastTick >= pdMS_TO_TICKS(1000))
    {
        lastTick = xTaskGetTickCount();
        if(volume > 9)
        lv_label_set_text_fmt(guider_ui.screen_label_18, "00:%d", volume); 
        else if(volume >= 0)
        lv_label_set_text_fmt(guider_ui.screen_label_18, "00:0%d", volume);
        if(volume > 0){
            schedule = (volume*100)/scheduleall;
            volume--;
            lv_arc_set_value(guider_ui.screen_arc_1, schedule);
            // printf("scheduieall = %d volume = %d  schedule = %d\r\n", scheduleall,volume,schedule);
        } else {
            startflag = false;
            volume = 0;
            schedule = (volume*100)/scheduleall;
            lv_arc_set_value(guider_ui.screen_arc_1, schedule);
            coffee_run_flag = 0;
            printf("Coffee volume finished\r\n");
        }       
        // if(schedule > 9)
        // lv_label_set_text_fmt(guider_ui.screen_label_18, "00:%d", schedule); 
        // else if(schedule >= 0)
        // lv_label_set_text_fmt(guider_ui.screen_label_18, "00:0%d", schedule);
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
    const TickType_t updateTimePeriod = pdMS_TO_TICKS(8000); 
    #if (LEFT_OR_COFFEE == RIGHT)
    const TickType_t machineInfoupdateTimePeriod = pdMS_TO_TICKS(7000); 
    #else
    const TickType_t machineInfoupdateTimePeriod = pdMS_TO_TICKS(6500); 
    #endif
    int time = 0;
    int machinetime = 0;
    ISL1208_Time_t time_read;
    bool isfillwater = false;
    // //读取时间
    // ISL1208_GetTime(&time_read);
    uint32_t runtime = 0;
    while (1){

   // 开机5s后补一次水
        TickType_t currentTime = xTaskGetTickCount();
        if (currentTime - lastUpdateTime >= updateTimePeriod && time < 1 ) {           
            GrindDataStr.data.cmd = CMDTYPE_SYSTEM_FILL_WATER;
            time++;
        } 
        if (currentTime - lastUpdateTime >= machineInfoupdateTimePeriod && machinetime < 2 ) {           
            GrindDataStr.data.cmd = CMDTYPE_SET_STEAMBLOCK;
            machinetime++;
        } 
        if (GrindDataStr.data.cmd == CMDTYPE_GRIND){

        }
        else if (GrindDataStr.data.cmd == CMDTYPE_SYSTEM_FILL_WATER){
            #if (LEFT_OR_COFFEE == LEFT)
            canSendFillWater();
            #endif
            
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_BEVERAGEMAKE_CHANNELB){
            coffee_run_flag = 1;
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftCoffee(1,volume);
            #else
                canSendRightCoffee(1,volume);
            #endif
            
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_MAKE_TEA){
            coffee_run_flag = 1;
            printf("do tea");
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftTeaProfile(GrindSetData.extract_time[teasetflag]);
                vTaskDelay(10 / portTICK_RATE_MS);
                canSendLeftTeaStart(1);
            #else
                canSendRightTeaProfile(GrindSetData.extract_time[teaflag]);
                vTaskDelay(10 / portTICK_RATE_MS);
                canSendRightTeaStart(1);
            #endif

            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if(GrindDataStr.data.cmd == CMDTYPE_MAKE_STEAM) {
            
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftSteam(1,volume);
            #else
            canSendRightSteam(1,volume);
            #endif
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_CANCEL_BEVERAGEMAKE_CHANNELB){
            coffee_run_flag = 0;
            volume = 0;
            lv_label_set_text_fmt(guider_ui.screen_label_18, "00:0%d", volume); 
            lv_arc_set_value(guider_ui.screen_arc_1, 0);
            #if (LEFT_OR_COFFEE == LEFT)
                canSendLeftCoffee(0,volume);
            #else
                canSendRightCoffee(0,volume);
            #endif
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } else if (GrindDataStr.data.cmd == CMDTYPE_SET_STEAMBLOCK) { 
            volume = GrindSetData.temp_steam;
            canSendsteamtemp(0,volume);
            volume = 0;
            GrindDataStr.data.cmd = CMDTYPE_SET_COFFEEBLOCK;
        } else if (GrindDataStr.data.cmd == CMDTYPE_SET_COFFEEBLOCK) { 
            #if(LEFT_OR_COFFEE == LEFT)
            int target = 0;
            #else
            int target = 1;
            #endif
            volume = GrindSetData.temp_coffee;
            canSendcoffeetemp(target,volume);
            volume = 0;
            GrindDataStr.data.cmd = CMDTYPE_SET_BREWBLOCK;
        } else if (GrindDataStr.data.cmd == CMDTYPE_SET_BREWBLOCK) { 
            #if(LEFT_OR_COFFEE == LEFT)
            int target = 0;
            #else
            int target = 1;
            #endif
            volume = GrindSetData.temp_brew;
            canSendbrewtemp(target,volume);
            volume = 0;
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        } 
        #if (LEFT_OR_COFFEE == LEFT)
        else if (GrindDataStr.data.cmd == CMDTYPE_HOTWATER) { 
            coffee_run_flag = 1;
            canSendhotwater(1,volume);
            GrindDataStr.data.cmd = CMDTYPE_GRIND;
        }
        #endif

        #if 0
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
            
            // 打印错误信息（如果可以使用printf）=
            // printf("UART4 Error!  SR: 0x%04lX\r\n", sr_register);
        }
        #endif
        if (dataIsReady){
            dataIsReady = 0;  
            getProtocol(rFrameBuf,&c);
            if (c.frame.cmd == CMDTYPE_SYSTEM_FILL_WATER){
            
            } 
        }
        #endif
        if (can_msg.data_is_ready){
            can_msg.data_is_ready = 0;
            uint8_t crc = 0;
            for(int i = 0;i < can_msg.rx_dlen;i++){
                crc += can_msg.rx_data[i];
                // printf("can_rx_data[%d] = %d\r\n",i,can_msg.rx_data[i]);
            }
            if (getCrc(can_msg.rx_efid)  == crc ) {
                    // printf("22222\r\n");
                if (getDestId(can_msg.rx_efid)  == HMI_ID ) {
                    // printf("cmd = 0x%02X\r\n", getCmdType(can_msg.rx_efid));
                    if ( getCmdType(can_msg.rx_efid) == FUNC_TEMPERATURE_B) {
                        int ret = can_msg.rx_data[1] << 8 | can_msg.rx_data[0];
                        blocktemp = (float)ret/10;
                        // printf("steam_temp = %f\r\n",blocktemp);
                        if(runtime >= 1000){
                            char temp_str[20];
                            sprintf(temp_str, "%.1f", blocktemp);
                            lv_label_set_text(guider_ui.screen_label_3, temp_str);
                            // lv_label_set_text(guider_ui.screen_label_temp, temp_str);
                        }
                    } else if (getCmdType(can_msg.rx_efid) == FUNC_TEMPERATURE_A){
                        #if (LEFT_OR_COFFEE == LEFT)
                        int ret = can_msg.rx_data[5] << 8 | can_msg.rx_data[4];
                        int ret2 = can_msg.rx_data[3] << 8 | can_msg.rx_data[2];   
                        brewtemp = (float)ret2/10;   
                        blocktemp = (float)ret/10;

                        if(runtime >= 1000){
                            char temp_str[20];
                            char temp_str1[20];
                            sprintf(temp_str, "%.1f", blocktemp);
                            lv_label_set_text(guider_ui.screen_label_4, temp_str);
                            sprintf(temp_str1, "%.1f", brewtemp);
                            lv_label_set_text(guider_ui.screen_label_1, temp_str1);
                        }      
                
                        #else
                        int ret = can_msg.rx_data[7] << 8 | can_msg.rx_data[6];
                        blocktemp = (float)ret/10;
                        // printf("coffee temp = %f\r\n",blocktemp);
                        if(runtime >= 1000){
                            char temp_str[20];
                            sprintf(temp_str, "%.1f", blocktemp);
                            lv_label_set_text(guider_ui.screen_label_4, temp_str);
                            // lv_label_set_text(guider_ui.screen_label_coffeetemp, temp_str);
                        }                               
                        #endif
                    } else if (getCmdType(can_msg.rx_efid) == FUNC_PRESSURE_CURRENT){ 
                        float ret = (float)can_msg.rx_data[0]/10;
                        // printf("ret %.1f\n",ret);
                        if(runtime >= 1000){
                            char temp_str[20];
                            sprintf(temp_str, "%.1f bar", ret);
                            lv_label_set_text(guider_ui.screen_label_16, temp_str);
                            // lv_label_set_text(guider_ui.screen_label_coffeetemp, temp_str);
                        }   
                    } 
                    #if (LEFT_OR_COFFEE == RIGHT)
                    else if (getCmdType(can_msg.rx_efid) == FUNC_VALVE){ 
                        int ret = can_msg.rx_data[5] << 8 | can_msg.rx_data[4];  
                        brewtemp = (float)ret/10;
                        // printf("brew %.1f\n",brewtemp);
                        if(runtime >= 1000){
                            char temp_str[20];
                            sprintf(temp_str, "%.1f", brewtemp);
                            lv_label_set_text(guider_ui.screen_label_1, temp_str);
                            // lv_label_set_text(guider_ui.screen_label_coffeetemp, temp_str);
                        }   
                    }
                    #endif
                }
            } else {
                printf("crc failed\r\n");
            }
        }
        // if(runtime % 500 == 0){
        //     printf("volume %d\r\n",volume);
        // }

        if(!startflag){
            lv_obj_add_flag(guider_ui.screen_img_stop, LV_OBJ_FLAG_HIDDEN);
            #if (LEFT_OR_COFFEE == LEFT)
            lv_obj_clear_flag(guider_ui.screen_btn_hotwater, LV_OBJ_FLAG_HIDDEN);
            #endif
            lv_obj_clear_flag(guider_ui.screen_img_21, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_rinse, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_coffee1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_coffee2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_coffee3, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_btn_coffee4, LV_OBJ_FLAG_HIDDEN);
            startflag = true;
        }
        //  else {
        //     lv_obj_clear_flag(guider_ui.screen_img_stop, LV_OBJ_FLAG_HIDDEN);
        //     lv_obj_add_flag(guider_ui.screen_img_21, LV_OBJ_FLAG_HIDDEN);
        //     lv_obj_add_flag(guider_ui.screen_btn_hotwater, LV_OBJ_FLAG_HIDDEN);
        //     lv_obj_add_flag(guider_ui.screen_btn_coffee1, LV_OBJ_FLAG_HIDDEN);
        //     lv_obj_add_flag(guider_ui.screen_btn_coffee2, LV_OBJ_FLAG_HIDDEN);
        //     lv_obj_add_flag(guider_ui.screen_btn_coffee3, LV_OBJ_FLAG_HIDDEN);
        //     lv_obj_add_flag(guider_ui.screen_btn_coffee4, LV_OBJ_FLAG_HIDDEN);
        // }
        CoffeeVolumeProcess();

        runtime += 5;
        vTaskDelay(pdMS_TO_TICKS(5));
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


