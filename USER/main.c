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


void vLCD_Refresh_LED_Task( void *pvParameters );
void vLvglTaskFunction( void * pvParameters );
void vflash(void *pvParameters);

TaskHandle_t xLCD_Refresh_LED_TaskHandle= NULL;  
TaskHandle_t xLvglTaskHandle = NULL;  
TaskHandle_t xFlashTaskHandle = NULL;
lv_ui guider_ui;

/* 全局触发标志 */
volatile uint8_t flash_request_flag = 0;
volatile uint32_t flash_request_value = 0;

void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // ���ø��ٵ�Ԫ
    DWT->CYCCNT = 0;                                // ����������
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            // �������ڼ�����
}


static UART_HandleTypeDef huart6;
// USART6初�?�化函数
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
int main(void)
{ 
	DWT_Init();
	BaseType_t xReturned;
	HAL_Init();      //��ʼ��HAL��
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // ʹ��HAL�⺯��
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0); // ��Ϊ������ȼ�  
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
	STM32_Clock_Init(336,25,2,7);  	//����ʱ��,168Mhz

	delay_init(168);               	//��ʼ����ʱ����
	LED_Init();					
	TIM2_Init();			 
	//KEY_Init();
    MX_USART6_UART_Init(); 
    printf("App is running.Version:%s Compiled on %s %s\n",version,__DATE__,__TIME__);
//	//Modbus_Init(9600); 
//	grind_time_init();		   
	
    gt911_init();
    //Read the data stored in the flash memory and print it.
    
        
    xReturned = xTaskCreate(vLCD_Refresh_LED_Task,"lcd_refresh_led_task",256,NULL,1,&xLCD_Refresh_LED_TaskHandle);
    if (xReturned != pdPASS) {
        printf("led task creation failed!\r\n");
    }
    xReturned = xTaskCreate(vLvglTaskFunction,"lvgl_task",1024,NULL,3,&xLvglTaskHandle);
    if (xReturned != pdPASS) {
        printf("lvgl task creation failed!\r\n");
    }
    xReturned = xTaskCreate(vflash, "flash_task", 256, NULL, 2, &xFlashTaskHandle);
    if (xReturned != pdPASS) {
        printf("Flash task creation failed!\r\n");
    }
    vTaskStartScheduler();  

    //	static uint32_t last_call = 0;

    // 	����С����10s��
    // 	Modbus_SendGrindTime(0);

    while (1)                                            // while������ѭ����������main�������н�������������Ӳ������
    {           
	}
}


void vLCD_Refresh_LED_Task( void *pvParameters )
{
	TickType_t xLastWakeTime_Refresh;
	const TickType_t xPeriod2 = pdMS_TO_TICKS( 50 );  //��������ֵ    5ms
	xLastWakeTime_Refresh = xTaskGetTickCount();   //��һ�µ�ǰʱ��	
	while(1)
	{
		vTaskDelayUntil( &xLastWakeTime_Refresh, xPeriod2 );//������ʱ1s������׼
		LED0=!LED0;
	}
}

//LVGL������
void vLvglTaskFunction(void *pvParameters) {
    printf("LVGL task is running. \r\n");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(5); // ��������5ms

    nv3401_gpio_init();
    nv3401_lcd_init();

    lv_init();
	lv_port_disp_init();   // ��Ҫʵ�ֵ���ʾ�ӿ�
	lv_port_indev_init();  // ��Ҫʵ�ֵĴ��ؽӿ�
	// ��ʼ��UI������������������
	setup_ui(&guider_ui);
	events_init(&guider_ui);

    while (1) {
        // �������ϴε�������������tick��������������
        static TickType_t xLastTickCount = 0;
        TickType_t xCurrentTickCount = xTaskGetTickCount();
        uint32_t elapsed_ticks = xCurrentTickCount - xLastTickCount;
        xLastTickCount = xCurrentTickCount;

        // ����LVGLʱ��
        lv_tick_inc(elapsed_ticks * portTICK_PERIOD_MS); // portTICK_PERIOD_MS��ÿ��tick�ĺ�����

        // ����LVGL����
        lv_task_handler();

        // ��ȷ��ʱ����֤��������
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}

void vflash(void *pvParameters) {
    uint32_t read_back_data;

        for (;;) {
        if (flash_request_flag) {
            flash_request_flag = 0;  // 清除标志

            printf("FlashTask: request to write %lu\r\n", flash_request_value);

            /* 解锁 Flash */
            FLASH_Init();

            /* 擦除 sector 11 */
            if (FLASH_EraseSector(USER_FLASH_SECTOR) == HAL_OK) {
                if (FLASH_WriteWord(0x080E0000, flash_request_value) == HAL_OK) {

                    printf("FlashTask: write OK\r\n");
                } else {
                    printf("FlashTask: write FAIL\r\n");
                }
            } else {
                printf("FlashTask: erase FAIL\r\n");
            }
            read_back_data = FLASH_ReadWord(USER_FLASH_START_ADDR);
            printf("Data read: 0x%08lX\r\n", read_back_data);
            HAL_FLASH_Lock();
        }
        
        vTaskDelay(pdMS_TO_TICKS(10)); // 避免空转，占用CPU
    }
}