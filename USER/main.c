#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usmart.h"
#include "touch.h"
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

void vLCD_Refresh_LED_Task( void *pvParameters );
void vLvglTaskFunction( void * pvParameters );
void vflash(void *pvParameters);

TaskHandle_t xLCD_Refresh_LED_TaskHandle= NULL;  
TaskHandle_t xLvglTaskHandle = NULL;  //LVGL相关的任务句柄  显示任务
TaskHandle_t xFlashTaskHandle = NULL;
lv_ui guider_ui;

// 在全局范围定义这些变量
volatile uint32_t current_grind_time = 10;      // 当前研磨时间
volatile uint32_t last_stored_grind_time = 0;   // 上次存储的研磨时间
volatile uint8_t grind_time_changed = 0;        // 改变标志

/************************************************
 WKS STM32F407VET6核心板
 触摸屏实验-HAL库函数版
************************************************/
void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 启用跟踪单元
    DWT->CYCCNT = 0;                                // 计数器清零
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            // 启用周期计数器
}
void grind_time_init(void) {
    uint32_t saved_time;
    int ret = FLASH_LoadConfig(&saved_time);
    
    if (ret == 1) {
        // 成功加载保存的时间
        current_grind_time = saved_time;
        printf("从Flash加载研磨时间: %d\n", current_grind_time);
    } else if (ret == 0) {
        // 没有有效数据，使用默认值
        current_grind_time = 10;
        printf("使用默认研磨时间: %d\n", current_grind_time);
    } else {
        // CRC校验失败，使用默认值
        current_grind_time = 10;
        printf("CRC校验失败，使用默认研磨时间: %d\n", current_grind_time);
    }
}

int main(void)
{ 
	DWT_Init();
	BaseType_t xReturned;
	HAL_Init();      //初始化HAL库
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // 使用HAL库函数
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0); // 设为最低优先级  
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);	
	STM32_Clock_Init(336,25,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	usmart_dev.init(84); 		        //初始化USMART
	LED_Init();										//初始化LED
	TIM2_Init();							  // 初始化TIM2		
	KEY_Init();						          //初始化KEY

	LCD_Init();								  // 初始化LCD
//	//Modbus_Init(9600); // 初始化Modbus
//	//grind_time_init();     //初始化时间			   
	tp_dev.init();				          //触摸屏初始化 
//	
	lv_init();
	lv_port_disp_init();   // 你要实现的显示接口
	lv_port_indev_init();  // 你要实现的触控接口
	// 初始化UI必须在任务上下文中
	setup_ui(&guider_ui);
	events_init(&guider_ui);

	xTaskCreate(vLCD_Refresh_LED_Task,"lcd_refresh_led_task",256,NULL,1,&xLCD_Refresh_LED_TaskHandle);
	xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
	xTaskCreate(vflash, "flash_task", 1024, NULL, 2, &xFlashTaskHandle);
	vTaskStartScheduler();  //启动调度器，任务开始执行

//	static uint32_t last_call = 0;

// 	发送小杯（10s）
// 	Modbus_SendGrindTime(0);

    while (1)                                            // while函数死循环，不能让main函数运行结束，否则会产生硬件错误
    {           
	}
}


void vLCD_Refresh_LED_Task( void *pvParameters )
{
	TickType_t xLastWakeTime_Refresh;
	const TickType_t xPeriod2 = pdMS_TO_TICKS( 100 );  //配置周期值    5ms
	xLastWakeTime_Refresh = xTaskGetTickCount();   //读一下当前时间	
	while(1)
	{
		vTaskDelayUntil( &xLastWakeTime_Refresh, xPeriod2 );//绝对延时1s，更精准
		LED0=!LED0;
	}
}

//LVGL任务函数
void vLvglTaskFunction(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(5); // 任务周期5ms

    while (1) {
        // 计算自上次调用以来经过的tick数（即毫秒数）
        static TickType_t xLastTickCount = 0;
        TickType_t xCurrentTickCount = xTaskGetTickCount();
        uint32_t elapsed_ticks = xCurrentTickCount - xLastTickCount;
        xLastTickCount = xCurrentTickCount;

        // 更新LVGL时间
        lv_tick_inc(elapsed_ticks * portTICK_PERIOD_MS); // portTICK_PERIOD_MS是每个tick的毫秒数

        // 处理LVGL任务
        lv_task_handler();

        // 精确延时，保证任务周期
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}

void vflash(void *pvParameters) {
    // 初始化：读取之前存储的值
    grind_time_init();
    
    // 设置初始值
    last_stored_grind_time = current_grind_time;
    
    for (;;) {
        // 检查是否需要存储
        if (grind_time_changed) {
            printf("检测到研磨时间改变: %d -> %d\n", last_stored_grind_time, current_grind_time);
            
            // 执行Flash存储操作
            FLASH_StoreConfig(current_grind_time);
            
            // 更新上次存储的值
            last_stored_grind_time = current_grind_time;
            
            // 清除改变标志
            grind_time_changed = 0;
            
            // 给Flash操作完成时间（可选）
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        
        // 短暂延时，减少CPU占用
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}