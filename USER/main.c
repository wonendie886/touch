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
#include "modbus.h"
#include "flash.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "gt911.h"
#include "mbrtu_master.h"
#include "modbus.h"
#include "can.h" 
#include "stm32f4xx_hal.h"      // 为 CanRxMsgTypeDef 等

void vLvglTaskFunction( void * pvParameters );
void vModbusTask(void *pvParameters);
void vGrindingControlTask(void *pvParameters);

TaskHandle_t xLCD_Refresh_LED_TaskHandle= NULL;  
TaskHandle_t xLvglTaskHandle = NULL;  
TaskHandle_t xFlashTaskHandle = NULL;
TaskHandle_t xGrindingControlTaskHandle = NULL; 
lv_ui guider_ui;


volatile uint8_t flash_request_flag = 0;
flash_store_t flash_write_data;
bool isGrindProgress = false;
bool isGrindRunning = false;
bool isGrindMode = MODE_TIME;
bool timerStart = false;
uint32_t resetTime = 0;

// 接收完成：从 HAL 的 pRxMsg 读取数据，转交给 CAN_UserRxCb，然后重新使能接收
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan_if)
{
    CanRxMsgTypeDef *r = hcan_if->pRxMsg;
    uint8_t data[8];
    uint8_t i;
    for (i = 0; i < r->DLC && i < 8; i++) data[i] = r->Data[i];
    for (; i < 8; i++) data[i] = 0x00;

    uint8_t is_ext = 0;
    uint32_t id = 0;
#ifdef CAN_Id_Extended
    if (r->IDE == CAN_Id_Extended) {
        is_ext = 1; id = r->ExtId;
    } else {
        is_ext = 0; id = r->StdId;
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
    CAN_UserRxCb(is_ext, id, r->DLC, data);

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

/**
 * 将所有研磨进度标签设置为相同的文本
 * @param text 要设置的文本内容
 */
void set_all_grinding_labels_text(const char* text)
{
//    lv_label_set_text(guider_ui.screen_label_7, text);
    lv_label_set_text(guider_ui.screen_label_8, text);
//   lv_label_set_text(guider_ui.screen_label_9, text);
}

/**
* 根据研磨目标设置对应标签的文本
* @param target 研磨目标 (1=标签7, 2=标签8, 3=标签9)
* @param text 要设置的文本内容
*/
// void set_grinding_label_text_by_target(int target, const char* text)
// {
//    switch (target) {
//        case 1:
//            lv_label_set_text(guider_ui.screen_label_7, text);
//            break;
//        case 2:
// //            lv_label_set_text(guider_ui.screen_label_8, text);
//            break;
//        case 3:
//            lv_label_set_text(guider_ui.screen_label_8, text);
//            break;
//        default:
//            break;
//    }
// }

/**
 * 根据研磨目标和数值设置对应标签的文本
 * @param target 研磨目标 (1=标签7, 2=标签8, 3=标签9)
 * @param value 要显示的数值
 */
void set_grinding_label_text_by_target_with_value(int target, int value)
{
    char buffer[32];
    if(isGrindMode == MODE_TIME){
        sprintf(buffer, "%0.1fs", (float)value/10.0f);
    }else{
        sprintf(buffer, "%0.1fg", (float)value/10.0f);
    }
    
    lv_label_set_text(guider_ui.screen_label_8, buffer);
}

void set_kr_current_time(int value)
{
    char buffer[32];
    sprintf(buffer, "%0.1f", (float)value/10.0f);
    lv_label_set_text(guider_ui.screen_label_2, buffer);
}
void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; 
    DWT->CYCCNT = 0;                                
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;           
}

UART_HandleTypeDef huart6;
// USART6初始化函数
static void MX_USART6_UART_Init(void)
{
    __HAL_RCC_USART6_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;       
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6; 
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    huart6.Instance = USART6;
    huart6.Init.BaudRate = 115200;
    huart6.Init.WordLength = UART_WORDLENGTH_8B;
    huart6.Init.StopBits = UART_STOPBITS_1;
    huart6.Init.Parity = UART_PARITY_NONE;
    huart6.Init.Mode = UART_MODE_TX; 
    huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart6.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&huart6) != HAL_OK)
    {
    }
}
// USART6 for printf 
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

const char version[12] = "MRC_V1.0.0";
extern UART_HandleTypeDef huart4;
extern MBRTUMaterTypeDef MbRtu;
extern uint32_t rxCount;
extern uint8_t RxBuf[100];
extern int grinding_target;  // 研磨目标: 1-对应文本7, 2-对应文本8, 3-对应文本9
extern uint16_t start_flag;              // 按钮4的启动标志位

SemaphoreHandle_t xSharedMutex;
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
	TIM2_Init();	
	//KEY_Init();
    MX_USART6_UART_Init(); 
    
    printf("App is running.Version:%s Compiled on %s %s\n",version,__DATE__,__TIME__);
    modbus_init();

    gt911_init();

    flashDataInit();

    xSharedMutex = xSemaphoreCreateMutex();
    xSemaphoreGive(xSharedMutex);
    
	xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
    xTaskCreate(vModbusTask,"modbus_task",512,NULL,3,&xLvglTaskHandle);
    xTaskCreate(vGrindingControlTask, "grinding_control_task", 1024, NULL, 2, &xGrindingControlTaskHandle);
	vTaskStartScheduler();  


    while (1)                                            
    {           
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
    images_init(&guider_ui);

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

extern uint16_t start_flag;
extern uint16_t Currenttargetime;
// 合并后的研磨控制任务，包含原来的研磨监控和按钮4检测功能
// 研磨控制任务



void sendStartCmd()
{   
    if (!isGrindRunning) {
            int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_ENABLE, 1, 100);

            if(ret != 0){
                printf("ret == %d\n",ret);
            }
            isGrindProgress = true;
            ///@todo change png to stop

            printf("send start cmd\r\n");
        // } else {
        //     printf("send start failed\r\n");
        // }
    }
}

void sendStopCmd()
{
    if (isGrindRunning) {
        int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_ENABLE, 0, 100);
        if ( ret == 0) {
            /// start 3S timer
            timerStart = true;
            resetTime = 0;
            ///@todo change png to start

            printf("send stop cmd\r\n");
        } else {
            printf("ret == %d\r\n",ret);
        }
    }
    
}

volatile uint8_t isStartMotor = 0;
volatile uint8_t resetFlag = 0;
volatile uint16_t register_values[3];  
uint8_t grindButtonStatus = 0;
void vModbusTask(void *pvParameters) {
    uint16_t initialization_data[2] = {0};
    initialization_data[0] = GrindSetData.time_1;
    initialization_data[1] = GrindSetData.weight_1;

    ///@todo The first transmission of Modbus always fails
    MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 2, 100, register_values);
    vTaskDelay(pdMS_TO_TICKS(100));

    //Send the initial weight and time down
    int ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 0x01, INDEX_GRIND_TIME, 2, initialization_data, 200);
    if(ret == 0) {
        printf("send initial weight and time success\r\n");
    } else {
        printf("send initial weight and time failed\r\n");
    }
    vTaskDelay(pdMS_TO_TICKS(100));

    uint16_t wBuffer[5] = {0};

    Currenttargetime = GrindSetData.time_1;
    while (1){
        wBuffer[INDEX_GRIND_ENABLE] = isStartMotor;
        wBuffer[INDEX_GRIND_MODE] = MODE_TIME;
        wBuffer[INDEX_GRIND_TIME] = Currenttargetime;
        wBuffer[INDEX_GRIND_WEIGHT] = 0;
        wBuffer[INDEX_GRIND_RESET] = resetFlag;
        int ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 0x01, INDEX_GRIND_ENABLE, 5,wBuffer, 100);

        if (resetFlag){
            resetFlag = 0;
        }
        if (ret != 0) {
            printf("ret: %d\n",ret);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
        int ret_progress = MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 3, 100, register_values);
        if (ret_progress != 0) {
            printf("ret_progress = %d\r\n",ret_progress);
        }

        if (grindButtonStatus != register_values[INDEX_GRIND_BUTTON]){
            grindButtonStatus = register_values[INDEX_GRIND_BUTTON];

            if(start_flag == STATUS_IN_GRIND_STOP){
                start_flag = STATUS_IN_GRIND_START;
            } else {
                start_flag = STATUS_IN_GRIND_STOP;
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vGrindingControlTask(void *pvParameters) {
    uint16_t time = 0 ;
    char progress_text[32];
    bool isStartFlag = 0;
    uint16_t motorTimer = 0;
    static uint8_t motor_running_prev = 0; 
    for (;;) {
        motor_running_prev = register_values[INDEX_GRIND_MOTOR_RUNNING]; 
        if(start_flag == STATUS_IN_GRIND_START) {
            isStartMotor = 1;
            if (!register_values[INDEX_GRIND_MOTOR_RUNNING]) {
                if (!isGrindProgress) {
                    motorTimer = 0;
                }
                timerStart = false;
                resetTime = 0;
     
                isGrindProgress = true;
                lv_obj_set_style_img_opa(guider_ui.screen_img_8, 188, LV_PART_MAIN | LV_STATE_DEFAULT);
                printf("send start cmd\r\n");
            }
        } else {
            isStartMotor = 0;
            if (register_values[INDEX_GRIND_MOTOR_RUNNING]) {
                ///@todo change png to start
                lv_obj_set_style_img_opa(guider_ui.screen_img_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

                /// start 3S timer
                timerStart = true;
                resetTime = 0;
                stop_spinner();
                printf("send stop cmd\r\n");
            }

            /// check resetTime == 3S, then send modbus reset cmd, then resetTime = 0 change png to start,update ui time = 0,isGrindProgress = false
            
            if(resetTime == 3000){
                printf("resetFlag = 1\r\n");
                resetFlag = 1;
                timerStart = false;
                resetTime = 0;
                motorTimer = 0;

                set_kr_current_time(0);

                isGrindProgress = false;
                lv_obj_set_style_img_opa(guider_ui.screen_img_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                
                vTaskDelay(pdMS_TO_TICKS(20));
            }
            
        }

        if (isGrindProgress) {
            ///wait for start   
            static uint8_t motor_prev_state = 0;            
           
            if (register_values[0] == 1) {
                //isGrindRunning = true;
                isStartFlag = true;
                motorTimer += 100;
                // 只有当电机从停止状态转为运行状态时才启动动画
                
                if(motor_prev_state == 0 && register_values[0] == 1) {
                    lv_anim_start(&a);
                }
 
                /// update ui
                set_kr_current_time(motorTimer/100);
            } 
            
            if (isStartFlag){
                if(motorTimer >= Currenttargetime){
                    printf("motorTimer is time out\n");
                    isGrindProgress = false;
                    start_flag = STATUS_IN_GRIND_STOP;
                    stop_spinner();
                    ///@TODO change png to start
                    lv_obj_set_style_img_opa(guider_ui.screen_img_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
             motor_prev_state = register_values[0];
        }
        if (timerStart){
            resetTime += 100;
        }
        LED0=!LED0;
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

#if 0
void vGrindingControlTask(void *pvParameters) {

    uint16_t register_values[2];  
    uint16_t weight_value[2];
    uint16_t time = 0 ;
    char progress_text[32];           // 进度文本缓冲区
    uint16_t initialization_data[2] = {0};
    initialization_data[0] = GrindSetData.time_1;
    initialization_data[1] = GrindSetData.weight_1;

    ///@todo The first transmission of Modbus always fails
    MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 2, 100, register_values);
    vTaskDelay(pdMS_TO_TICKS(100));

    //Send the initial weight and time down
    int ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 0x01, INDEX_GRIND_TIME, 2, initialization_data, 200);
    if(ret == 0) {
        printf("send initial weight and time success\r\n");
    } else {
        printf("ret == %d\r\n",ret);
    }

    for (;;) {
        if (isGrindMode == MODE_TIME) {
            if(start_flag == STATUS_IN_GRIND_START) {
                sendStartCmd();
            } else {
                /// ui status stop
                sendStopCmd();

                /// check resetTime == 3S, then send modbus reset cmd, then resetTime = 0 change png to start,update ui time = 0,isGrindProgress = false
                if(resetTime == 3000){
                    int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_RESET, 1, 100);
                    if (ret != 0){
                        printf("ret == %d\r\n",ret);
                    }
                    resetTime = 0 ; 

                    set_all_grinding_labels_text("0");

                    isGrindProgress = false;
                    lv_obj_add_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                    show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);
                }
                
            }

            if (isGrindProgress) {
                ///grind work progress
                /// read modbus data,get data
                int ret_progress = MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 2, 100, register_values);
                if (ret_progress == 0) {
                     /// check grind motor running status
                    /// running is false,,  check running time == target time（time mode）,then change png to start,update ui time = 0,isGrindProgress = false
                    if (register_values[0] == 1) {
                        set_all_grinding_labels_text("0");
                        isGrindRunning = true;
                        show_multiple_buttons(&guider_ui,guider_ui.screen_btn_4,1);
                        lv_obj_clear_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                        /// update ui
                        set_grinding_label_text_by_target_with_value(grinding_target, register_values[1]/100);
                        
                    } else {
                        isGrindRunning = false;
                        printf("Currenttargetime = %d,register_values[1] = %d\n",Currenttargetime,register_values[1]);                        
                        if(register_values[1] == 0){                     
                            isGrindProgress = false;
                            start_flag = STATUS_IN_GRIND_STOP;
                            ///@TODO change png to start
                            vTaskDelay(pdMS_TO_TICKS(1000));
                            lv_obj_add_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                            show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);
                        }
                    }
                }else{
                    printf("ret_progress == %d\r\n",ret_progress);
                }
                
            } else {
                ///grind ready
            }   
        } else {
             /// read modbus data,get data
            int ret_progress = MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 2, 100, weight_value);
            if(ret_progress == 0){
                /// check grind motor running status
                if (weight_value[0] == 1) {
                    isGrindRunning = true;
                    /// update ui
                    lv_obj_clear_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                    set_grinding_label_text_by_target_with_value(grinding_target, weight_value[1]);      
                }else{
                    isGrindRunning = false;
                    vTaskDelay(pdMS_TO_TICKS(1000));
                    lv_obj_add_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                    
                    //End of prompt
                }    
            }else{
                printf("ret_progress == %d\r\n",ret_progress);
            }
             /*if (isGrindProgress)
             {
                 /// update weight ui
                 /// check running status,running is false,update ui time = 0,isGrindProgress = false
             } else {
                /// check running status
                /// running is true,isGrindProgress = true
            }*/
           

        }
        if (timerStart){
            resetTime += 100;
        }
        
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
#endif 
