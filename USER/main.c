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
#include "protocol.h"
#include "can.h" 
#include "stm32f4xx_hal.h"      // 为 CanRxMsgTypeDef 等
#include "main.h"

extern volatile uint16_t Currenttargeweight;

void vLvglTaskFunction( void * pvParameters );
void vflash(void *pvParameters);
void vGrindingControlTask(void *pvParameters);

void vMainTask(void *pvParameters);

TaskHandle_t xLvglTaskHandle = NULL;  
TaskHandle_t xFlashTaskHandle = NULL;
TaskHandle_t xGrindingControlTaskHandle = NULL; 
TaskHandle_t xMainTaskHandle = NULL; 
lv_ui guider_ui;


volatile uint8_t flash_request_flag = 0;
flash_store_t flash_write_data;
bool isGrindProgress = false;
bool isGrindRunning = false;
bool isGrindMode = MODE_TIME;
bool timerStart = false;
uint32_t resetTime = 0;
int runtime = 0;

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
 * 根据研磨目标和数值设置对应标签的文本
 * @param target 研磨目标 (1=标签7, 2=标签8, 3=标签9)
 * @param value 要显示的数值
 */
void set_grinding_label_text_by_target_with_value(int target, int value)
{
    char buffer[32];
    if(isGrindMode == MODE_TIME){
        sprintf(buffer, "%0.1f", (float)value/10.0f);
        lv_label_set_text(guider_ui.screen_label_9, "s");
 
    }else{
        sprintf(buffer, "%0.1f", (float)value/10.0f);
        lv_label_set_text(guider_ui.screen_label_9, "g");
    }
    
    lv_label_set_text(guider_ui.screen_label_8, buffer);
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

SemaphoreHandle_t xSharedMutex;
/// 32K offset
#define APP_FLASH_OFFSET 0x0000
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
    // gt911_init();

    flashDataInit();
    
    CAN_Init_IT(500);
    CAN_ConfigFilterAcceptAll();
    CAN_StartReceive_IT();

    // xSharedMutex = xSemaphoreCreateMutex();
    // xSemaphoreGive(xSharedMutex);
	// xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
    //xTaskCreate(vGrindingControlTask, "grinding_control_task", 256, NULL, 2, &xGrindingControlTaskHandle);
    xTaskCreate(vMainTask, "vMainTask", 256, NULL, 2, &xMainTaskHandle);
	vTaskStartScheduler();  


    while (1)                                            
    {           
	}
}

static uint8_t buf[FRAME_MAX_LEN];
static struct Protocol c;
struct GrindData grindData;
void vMainTask(void *pvParameters)
{
    int len = 0;
    grindData.mode = MODE_WEIGHT;
    grindData.target = 180; ///18.0 g
    grindData.cmd_number = 0;
    grindData.cmd_state = CMD_STATE_IDLE;

    len = setGrindCmdType(buf, &grindData);
    while (1){
        sendData(buf, len);
        printf("send data");
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

void vflash(void *pvParameters) {
        // for (;;) {
        // if (flash_request_flag) {
        //     flash_request_flag = 0;  // 清除标志

        //     /* 解锁 Flash */
        //     FLASH_Init();

        //     /* 擦除 sector 11 */
        //     if (FLASH_EraseSector(USER_FLASH_SECTOR) == HAL_OK) {
        //         if (FLASH_WriteData(USER_FLASH_START_ADDR, (uint32_t*)&flash_write_data, 
        //                            sizeof(flash_store_t)/4) == HAL_OK) {

        //             printf("FlashTask: write OK\r\n");
        //         } else {
        //             printf("FlashTask: write FAIL\r\n");
        //         }
        //     } else {
        //         printf("FlashTask: erase FAIL\r\n");
        //     }
        //     // 读回验证
        //     flash_store_t read_data;
        //     uint32_t *src = (uint32_t*)USER_FLASH_START_ADDR;
        //     uint32_t *dst = (uint32_t*)&read_data;
        //     uint32_t size = sizeof(flash_store_t) / 4;
        //     for (uint32_t i = 0; i < size; i++) {
        //         dst[i] = src[i];
        //     }
            
        //     HAL_FLASH_Lock();
        // }
        
        vTaskDelay(pdMS_TO_TICKS(10)); // 避免空转，占用CPU
    // }
}


extern uint16_t start_flag;
extern uint16_t Currenttargetime;
// 合并后的研磨控制任务，包含原来的研磨监控和按钮4检测功能
// 研磨控制任务
container2_status_t container2_status = {0, 0, 0};

#if 0
void sendStartCmd()
{   
    if (!isGrindRunning) {
            int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_ENABLE, 1, 100);

            if(ret != 0){
                printf("ret == %d\n",ret);
            }
            isGrindProgress = true;
            ///@todo change png to stop
            timerStart = false;
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

void vGrindingControlTask(void *pvParameters) {

    uint16_t register_values[2];  
    uint16_t weight_value[2];
    uint32_t time = 0 ;
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

    static uint32_t self_timer_ms = 0;        // 以毫秒为单位的独立计时器
    static bool self_timer_active = false;    // 是否处于自计时状态（只在 register_values[0]==1 时累加）
    uint16_t last_register_running = 0;       // 上一次循环读到的 register_values[0]，用于检测 0 -> 1 的上升沿
    uint16_t last_weight_running = 0;   
    
    bool isAniRunning = false;
    for (;;) {

        if (isGrindMode == MODE_TIME) {
            // printf(" m start_flag == %d\r\n",start_flag);
            if(start_flag == STATUS_IN_GRIND_START) {
                // printf("1111111111111111111111111111111111111");
                sendStartCmd();
            } else {
                /// ui status stop
                sendStopCmd();

                /// check resetTime == 3S, then send modbus reset cmd, then resetTime = 0 change png to start,update ui time = 0,isGrindProgress = false
                if(start_flag == STATUS_IN_GRIND_SUSPEND && resetTime >= 2000){
                    int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_RESET, 1, 100);
                    if (ret != 0){
                        printf("ret == %d\r\n",ret);
                    }
                    resetTime = 0 ; 
                    self_timer_ms = 0;
                    set_all_grinding_labels_text("0");
                    
                    runtime = 0;
                    start_flag = STATUS_IN_GRIND_STOP;

                    isGrindProgress = false;
                    container2_status.end_flag = 1;
                    // printf("超时置1\n");
                    container2_status.hide_counter = 0; 
                    show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);
                }
                
            }
            
            if (isGrindProgress) {
                ///grind work progress
                /// read modbus data,get data
                int ret_progress = MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 2, 100, register_values);
                if (ret_progress == 0) {
                    uint32_t target_ms = 0;
                    if(grinding_target == 1){
                        target_ms = GrindSetData.time_1; // 转为毫秒上限
                    }else if(grinding_target == 3){
                        target_ms = GrindSetData.time_3;
                    }
                    printf("register_values[0] == %d\n",register_values[0]);
                    //  check grind motor running status
                    //  running is false,,  check running time == target time（time mode）,then change png to start,update ui time = 0,isGrindProgress = false
                    if (register_values[0] == 1) {
                        runtime += 160;
                        // printf("runtime = %d\n",runtime);
                        if (!isAniRunning){
                            isAniRunning = true;
                            // 启动动画
                        }
                        // 上升沿检测：从 0 -> 1 时启动/复位自计时器
                        if (last_register_running == 0) {
                            self_timer_active = true;
                           
                        } else {
                            // 连续处于 1 的情况：每个循环累加 100ms（本任务末尾 vTaskDelay 100ms）
                            if (self_timer_active) {
                                if (self_timer_ms + 150u <= target_ms) {
                                    self_timer_ms += 150u;
                                } else {
                                    self_timer_ms = target_ms; // cap 到目标
                                }
                            } else {
                                // 防护：如果意外为 false，则在这里启动
                                self_timer_active = true;
                                self_timer_ms = 100u;
                            }
                        }

                        // 将毫秒转换为 deciseconds（UI 显示函数中以 value/10 显示秒）
                        uint16_t display_value_ds = (uint16_t)(self_timer_ms / 100u);
                        set_grinding_label_text_by_target_with_value(grinding_target, display_value_ds);
                        isGrindRunning = true;
                        show_multiple_buttons(&guider_ui,guider_ui.screen_btn_4,1);
                        if (!container2_status.is_visible) {
                            lv_obj_clear_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                            container2_status.is_visible = 1;
                        }
                        /// update ui
                        
                    } else {
                        // printf("runtime = %d\n",runtime);
                        if (runtime >= Currenttargetime){
                            start_flag = STATUS_IN_GRIND_STOP;
                            runtime = 0;
                            }
                        if (isAniRunning) {
                            isAniRunning = false;
                            // stop_spinner();
                        }
                        isGrindRunning = false;
                        // self_timer_ms = register_values[1];
                        printf("Currenttargetime = %d,register_values[1] = %d\n",Currenttargetime,register_values[1]);                        
                        if(register_values[1] == 0){
                            if(start_flag == STATUS_IN_GRIND_SUSPEND){
                                isGrindProgress = false;
                            }else{
                                /* 停止时：若检测到刚从 1 -> 0（下位机结束），立即显示设定的 GrindSetData.time_1；随后重置自计时器，确保下次从 0 开始累加。 */
                                if (last_register_running == 1) {
                                    // 下降沿：下位机结束，显示你设置的最终时间（毫秒转 deciseconds）
                                    uint16_t display_value_ds = (uint16_t)(target_ms / 100u);
                                    set_grinding_label_text_by_target_with_value(grinding_target, display_value_ds);

                                    // 时间模式正常结束，设置标志位
                                    container2_status.end_flag = 1;
                                    // printf("结束置1\n");
                                    container2_status.hide_counter = 0; // 重置计数器

                                } 
                                // 重置：保证下次启动从 0 开始累加
                                self_timer_active = false;
                                self_timer_ms = 0;      

                                isGrindProgress = false;
                                start_flag = STATUS_IN_GRIND_STOP;
                                printf(" stop start_flag = %d\r\n",start_flag);
                            }
                            ///@TODO change png to start
                            show_multiple_buttons(&guider_ui,guider_ui.screen_btn_1,8);
                        }
                    }
                    // 保存上一次寄存器状态用于下一轮上升沿检测
                    last_register_running = register_values[0];
                }else{
                    printf("ret_progress == %d\r\n",ret_progress);
                }
                
            } else {
                ///grind ready
            }   

            if (time >= 3000) {
                sendHeartBeat(0);
            } 
        } else {
             /// read modbus data,get data
            int ret_progress = MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 2, 100, weight_value);
            if(ret_progress == 0){
                /// check grind motor running status
                if (weight_value[0] == 1) {
                    if (!isAniRunning){
                        isAniRunning = true;
                        // lv_anim_start(&a);
                    }
                    isGrindRunning = true;
                    /// update ui
                    if (!container2_status.is_visible) {
                        lv_obj_clear_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                        container2_status.is_visible = 1;
                    }
                    set_grinding_label_text_by_target_with_value(grinding_target, weight_value[1]);      
                }else{
                    if (isAniRunning) {
                        isAniRunning = false;
                        // stop_spinner();
                    }
                    isGrindRunning = false;                    
                    set_grinding_label_text_by_target_with_value(grinding_target, weight_value[1]);   

                    // 只有在从运行状态变为停止状态时才设置结束标志
                    if (last_weight_running == 1) {
                        container2_status.end_flag = 1;
                        // printf("重量置1\n");
                        container2_status.hide_counter = 0; // 重置计数器
                    }
                }
                last_weight_running = weight_value[0];    
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
           
            
            if (can_msg.data_is_ready){
                can_msg.data_is_ready = 0;
                uint8_t crc = 0;
                for(int i = 0;i < can_msg.rx_dlen;i++){
                    crc += can_msg.rx_data[i];
                }
                if (getCrc(can_msg.rx_efid)  == crc ) {
                    if (getDestId(can_msg.rx_efid)  == GRIND_HMI_ID ) {
                        if ( getCmdType(can_msg.rx_efid) == GRIND_HMI_ID_TARGET_WEIGHT) {
                            int weight = (can_msg.rx_data[3] << 24) | (can_msg.rx_data[2] << 16) 
                                        | (can_msg.rx_data[1] << 8) | can_msg.rx_data[0];
                            char str[50] = {0};

                            Currenttargeweight = weight;

                            sprintf(str, "%.1f", (float)Currenttargeweight / 10.0f);
                            lv_label_set_text_fmt(guider_ui.screen_label_4, "%s", str);
                            lv_label_set_text_fmt(guider_ui.screen_label_6, "%s", str);
                            int ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_WEIGHT, Currenttargeweight, 100);
                            if(ret != 0){
                                printf("ret == %d\n",ret);
                            }
                        } 
                    }
                } else {
                    printf("crc failed\r\n");
                }

            }

            if (time >= 3000) {
                sendHeartBeat(1);
            } 
        }
        if (timerStart){
            resetTime += 100;
        }

        time += 100;

        // printf("container2_status.end_flag = %d\r\n",container2_status.end_flag);
        // 检查是否需要隐藏容器2（只有在结束标志被设置且容器当前可见时才处理）
        if (container2_status.end_flag == 1 && container2_status.is_visible) {
            container2_status.hide_counter += 150; // 每次循环增加100ms
            // printf("Container2 hide counter: %d\n", container2_status.hide_counter);
            if (container2_status.hide_counter >= 3000) {
                lv_obj_add_flag(guider_ui.screen_cont_2, LV_OBJ_FLAG_HIDDEN);
                container2_status.is_visible = 0;
                container2_status.end_flag = 0;
                container2_status.hide_counter = 0;
                printf("Container2 hidden after normal completion\n");
            }
        }  
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
#endif
