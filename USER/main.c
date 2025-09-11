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
#include "task.h"
#include "gt911.h"
#include "mbrtu_master.h"
#include "modbus.h"


void vLCD_Refresh_LED_Task( void *pvParameters );
void vLvglTaskFunction( void * pvParameters );
void vflash(void *pvParameters);
// void vGrindingMonitorTask(void *pvParameters);  
// void vButton4MonitorTask(void *pvParameters); 
void vGrindingControlTask(void *pvParameters);

TaskHandle_t xLCD_Refresh_LED_TaskHandle= NULL;  
TaskHandle_t xLvglTaskHandle = NULL;  
TaskHandle_t xFlashTaskHandle = NULL;
// TaskHandle_t xGrindingMonitorTaskHandle = NULL; 
// TaskHandle_t xButton4MonitorTaskHandle = NULL; 
TaskHandle_t xGrindingControlTaskHandle = NULL; 
lv_ui guider_ui;

/* 全局触发标志 */
volatile uint8_t flash_request_flag = 0;
flash_store_t flash_write_data;

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
int main(void)
{ 
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

    modbus_test();
    
	xTaskCreate(vLCD_Refresh_LED_Task,"lcd_refresh_led_task",256,NULL,1,&xLCD_Refresh_LED_TaskHandle);
	xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
	xTaskCreate(vflash, "flash_task", 1024, NULL, 2, &xFlashTaskHandle);
    // xTaskCreate(vGrindingMonitorTask, "grinding_monitor_task", 128, NULL, 2, &xGrindingMonitorTaskHandle);
    // xTaskCreate(vButton4MonitorTask, "button4_monitor_task", 128, NULL, 2, &xButton4MonitorTaskHandle);  
    xTaskCreate(vGrindingControlTask, "grinding_control_task", 256, NULL, 2, &xGrindingControlTaskHandle);
	vTaskStartScheduler();  


    while (1)                                            
    {           
	}
}


void vLCD_Refresh_LED_Task( void *pvParameters )
{
	TickType_t xLastWakeTime_Refresh;
	const TickType_t xPeriod2 = pdMS_TO_TICKS( 50 );  
	xLastWakeTime_Refresh = xTaskGetTickCount();   
	while(1)
	{
		vTaskDelayUntil( &xLastWakeTime_Refresh, xPeriod2 );
		LED0=!LED0;
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
        for (;;) {
        if (flash_request_flag) {
            flash_request_flag = 0;  // 清除标志

            /* 解锁 Flash */
            FLASH_Init();

            /* 擦除 sector 11 */
            if (FLASH_EraseSector(USER_FLASH_SECTOR) == HAL_OK) {
                if (FLASH_WriteData(USER_FLASH_START_ADDR, (uint32_t*)&flash_write_data, 
                                   sizeof(flash_store_t)/4) == HAL_OK) {

                    printf("FlashTask: write OK\r\n");
                } else {
                    printf("FlashTask: write FAIL\r\n");
                }
            } else {
                printf("FlashTask: erase FAIL\r\n");
            }
            // 读回验证
            flash_store_t read_data;
            uint32_t *src = (uint32_t*)USER_FLASH_START_ADDR;
            uint32_t *dst = (uint32_t*)&read_data;
            uint32_t size = sizeof(flash_store_t) / 4;
            for (uint32_t i = 0; i < size; i++) {
                dst[i] = src[i];
            }
            // 添加数据打印
//            printf("FlashTask: Data read back verification:\r\n");
//            printf("  label1_text: %s\r\n", read_data.label1_text);
//            printf("  label2_text: %s\r\n", read_data.label2_text);
//            printf("  label3_text: %s\r\n", read_data.label3_text);
//            printf("  label4_text: %s\r\n", read_data.label4_text);
//            printf("  label5_text: %s\r\n", read_data.label5_text);
//            printf("  label6_text: %s\r\n", read_data.label6_text);
            
            HAL_FLASH_Lock();
        }
        
        vTaskDelay(pdMS_TO_TICKS(10)); // 避免空转，占用CPU
    }
}

// 研磨监控任务
/*void vGrindingMonitorTask(void *pvParameters) {
    uint16_t grinding_status = 0;     // 研磨状态 (来自输入寄存器0x0001)
    uint16_t grinding_progress = 0;   // 研磨进度 (来自输入寄存器0x0002)
    char progress_text[32];           // 进度文本缓冲区
    extern int grinding_target;      // 研磨目标

    for (;;) {
        // 读取输入寄存器0x0001的研磨状态
        int ret_status = MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 1, 100, &grinding_status);
        if (ret_status == 0) {  // 读取成功
            if (grinding_status == 0) {  // 没有在研磨
                // 将文本7、8、9清零
                lv_label_set_text(guider_ui.screen_label_7, "0");
                lv_label_set_text(guider_ui.screen_label_8, "0");
                lv_label_set_text(guider_ui.screen_label_9, "0");
                //启动标志位置零
                start_flag = grinding_status;              // 按钮4的启动标志位
            } else {  // 正在研磨
                // 读取当前研磨进度 (输入寄存器0x0002)
                int ret_progress = MBRTUMasterReadInputRegisters(&MbRtu, 0x01, INDEX_GRIND_DATA, 1, 100, &grinding_progress);
                if (ret_progress == 0) {  // 读取成功
                    // 根据grinding_target决定在哪个文本上显示进度
                    sprintf(progress_text, "%d", grinding_progress);
                    switch (grinding_target) {
                        case 1:  // 显示在文本7上
                            lv_label_set_text(guider_ui.screen_label_7, progress_text);
                            break;
                        case 2:  // 显示在文本8上
                            lv_label_set_text(guider_ui.screen_label_8, progress_text);
                            break;
 ret_progress                       case 3:  // 显示在文本9上
                            lv_label_set_text(guider_ui.screen_label_9, progress_text);
                            break;
                        default:
                            // 如果没有设置目标，则不显示
                            break;
                    }
                }
            }
        }
        
        // 每100ms读取一次
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vButton4MonitorTask(void *pvParameters) {
    static uint32_t zero_start_time = 0;     // 置零开始时间
    static uint8_t is_zero_state = 0;        // 是否处于置零状态

    u16 reg = 1 ;
    for (;;) {
   
            // 检查按钮4的状态
            if (start_flag == 0) {  // 按钮4触发的标志位为0
                if (!is_zero_state) {
                    is_zero_state = 1;
                    zero_start_time = xTaskGetTickCount();  // 记录取零开始时间
                } else {
                    // 检查是否超过3秒
                   if ((xTaskGetTickCount() - zero_start_time) > pdMS_TO_TICKS(3000)) {
                       // 超过3秒，重置文本数据
                       lv_label_set_text(guider_ui.screen_label_7, "0");
                       lv_label_set_text(guider_ui.screen_label_8, "0");
                       lv_label_set_text(guider_ui.screen_label_9, "0");
    
                       // 通过Modbus下发数据0到保持寄存器0x0003
                       MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_TIME, 0, 100);
    
                       // 重置状态以避免重复执行
                       is_zero_state = 0;
                   }
               }
           } else {
               // 按钮4标志位不为0，清除置零状态
               is_zero_state = 0;
           }
    
           // 每100ms检查一次
           vTaskDelay(pdMS_TO_TICKS(100));
    }
}*/
extern uint16_t start_flag; 
// 合并后的研磨控制任务，包含原来的研磨监控和按钮4检测功能
// 研磨控制任务
void vGrindingControlTask(void *pvParameters) {
    uint16_t grinding_status = 0;     // 当前设备状态 (来自输入寄存器0x0001)
    uint16_t grinding_progress = 0;   // 当前研磨进度 (来自输入寄存器0x0002)
    char progress_text[32];           // 进度文本缓冲区

    // 状态跟踪
    static uint16_t last_status = 0xFFFF; // 上一次设备状态 (初始化为无效值)
    static uint32_t stop_timer = 0;       // 停止计时器
    static uint8_t is_stop_pressed = 0;   // 是否进入停止计时
    static uint8_t reset_performed = 0;   // 是否已执行过重置

    // 命令状态
    static uint8_t last_command_sent = 0;     // 上次命令 (0: 停止, 1: 启动)
    static uint8_t command_acknowledged = 1;  // 是否已确认（初始可发命令）

    for (;;) {
        // 1. 读取设备运行状态
        int ret_status = MBRTUMasterReadInputRegisters(
            &MbRtu, 0x01, INDEX_GRIND_MOTOR_RUNNING, 1, 100, &grinding_status
        );

        if (ret_status == 0) {
            // === 仅在状态变化时处理 ===
            if (grinding_status != last_status) {
                if (grinding_status != 0) {
                    // ---- 设备从停止 → 运行 ----
                    printf("设备开始运行\r\n");
                    command_acknowledged = 1; 
                    is_stop_pressed = 0;
                    reset_performed = 0;
                } else {
                    // ---- 设备从运行 → 停止 ----
                    if (last_command_sent == 1) {
                        // 自然结束
                        command_acknowledged = 1;
                        last_command_sent = 0;
                        start_flag = 0;  // ⭐ 修复：自然结束时同步清零启动标志
                        printf("设备自动结束，状态已重置为停止\r\n");
                    } else {
                        // 用户主动停止
                        command_acknowledged = 1;
                        printf("设备已停止（用户停止）\r\n");
                    }

                    // 开始3秒计时
                    is_stop_pressed = 1;
                    stop_timer = xTaskGetTickCount();
                    reset_performed = 0;
                }

                last_status = grinding_status; // 保存当前状态
            }

            // === 如果正在运行则更新进度 ===
            if (grinding_status != 0) {
                int ret_progress = MBRTUMasterReadInputRegisters(
                    &MbRtu, 0x01, INDEX_GRIND_DATA, 1, 100, &grinding_progress
                );
                if (ret_progress == 0) {
                    sprintf(progress_text, "%d", grinding_progress);
                    switch (grinding_target) {
                        case 1: lv_label_set_text(guider_ui.screen_label_7, progress_text); break;
                        case 2: lv_label_set_text(guider_ui.screen_label_8, progress_text); break;
                        case 3: lv_label_set_text(guider_ui.screen_label_9, progress_text); break;
                        default: break;
                    }
                }
            }
        }

        // 2. 停止超过3秒 → 重置
        if (is_stop_pressed && !reset_performed) {
            if ((xTaskGetTickCount() - stop_timer) > pdMS_TO_TICKS(3000)) {
                printf("停止超过3秒，重置所有状态\r\n");

                // 清零显示
                lv_label_set_text(guider_ui.screen_label_7, "0");
                lv_label_set_text(guider_ui.screen_label_8, "0");
                lv_label_set_text(guider_ui.screen_label_9, "0");

                // 下发复位命令
                MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_RESET, 0, 100);

                reset_performed = 1;
                is_stop_pressed = 0;
            }
        }

        // 3. 启停命令逻辑（仅在命令已确认时允许发新命令）
        if (start_flag == 1 && command_acknowledged && last_command_sent != 1) {
            if (MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_ENABLE, 1, 100) == 0) {
                printf("启动命令已发送\r\n");
                last_command_sent = 1;
                command_acknowledged = 0; // 等待设备确认
            }
        } 
        else if (start_flag == 0 && command_acknowledged && last_command_sent != 0) {
            if (MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_ENABLE, 0, 100) == 0) {
                printf("停止命令已发送\r\n");
                last_command_sent = 0;
                command_acknowledged = 0; // 等待设备确认
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


