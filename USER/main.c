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
TaskHandle_t xLvglTaskHandle = NULL;  //LVGL��ص�������  ��ʾ����
TaskHandle_t xFlashTaskHandle = NULL;
lv_ui guider_ui;

// ��ȫ�ַ�Χ������Щ����
volatile uint32_t current_grind_time = 10;      // ��ǰ��ĥʱ��
volatile uint32_t last_stored_grind_time = 0;   // �ϴδ洢����ĥʱ��
volatile uint8_t grind_time_changed = 0;        // �ı��־

/************************************************
 WKS STM32F407VET6���İ�
 ������ʵ��-HAL�⺯����
************************************************/
void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // ���ø��ٵ�Ԫ
    DWT->CYCCNT = 0;                                // ����������
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            // �������ڼ�����
}



static UART_HandleTypeDef huart6;
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
int main(void)
{ 
/*	DWT_Init();
	BaseType_t xReturned;
	HAL_Init();      //��ʼ��HAL��
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // ʹ��HAL�⺯��
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0); // ��Ϊ������ȼ�  
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);*/	
    HAL_Init();
	STM32_Clock_Init(336,25,2,7);  	//����ʱ��,168Mhz

    MX_USART6_UART_Init();
/*	delay_init(168);               	//��ʼ����ʱ����

	LED_Init();					
	TIM2_Init();				 
	//KEY_Init();
    MX_USART6_UART_Init(); 

    printf("App is running.Version:%s Compiled on %s %s\n",version,__DATE__,__TIME__);
//	//Modbus_Init(9600); 
//	grind_time_init();		   
	
    gt911_init();*/
        
    HAL_StatusTypeDef status;
    uint32_t test_data = 0x12345678;
    uint32_t read_back_data;

    /* 1. 初始化Flash，解锁 */
    status = FLASH_Init();
    if (status != HAL_OK) {
        // 打印解锁失败
        printf("Flash unlock failed\r\n");
        
    }

    /* 2. 擦除扇区 (写入前必须先擦除!) */
    status = FLASH_EraseSector(USER_FLASH_SECTOR);
    if (status != HAL_OK) {
        // 打印擦除失败
        printf("Flash erase failed\r\n");
    }

    /* 3. 写入一个字的数据 */
    status = FLASH_WriteWord(USER_FLASH_START_ADDR, test_data);
    if (status != HAL_OK) {
        // 打印写入失败
        printf("Flash write failed\r\n");
    }

    /* 4. 读取刚写入的数据 */
    read_back_data = FLASH_ReadWord(USER_FLASH_START_ADDR);

    printf("Data read: 0x%08lX\r\n", read_back_data);

    /* 5. 示例：写入多个数据 */
    uint32_t data_array[4] = {0xAAAAAAAA, 0x55555555, 0x00000000, 0xFFFFFFFF};
    status = FLASH_WriteData(USER_FLASH_START_ADDR + 0x100, data_array, 4); // 偏移一定地址写入

    /* 最后，可以根据需要决定是否重新上锁Flash */
    HAL_FLASH_Lock();

    //	xTaskCreate(vLCD_Refresh_LED_Task,"lcd_refresh_led_task",256,NULL,1,&xLCD_Refresh_LED_TaskHandle);
    //	xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
    //	xTaskCreate(vflash, "flash_task", 1024, NULL, 2, &xFlashTaskHandle);
    //	vTaskStartScheduler();  //����������������ʼִ��

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

/*void vflash(void *pvParameters) {
    // ��ʼ������ȡ֮ǰ�洢��ֵ
    grind_time_init();
    
    // ���ó�ʼֵ
    last_stored_grind_time = current_grind_time;
    
    for (;;) {
        // ����Ƿ���Ҫ�洢
        if (grind_time_changed) {
           // printf("��⵽��ĥʱ��ı�: %d -> %d\n", last_stored_grind_time, current_grind_time);
            
            // ִ��Flash�洢����
            FLASH_StoreConfig(current_grind_time);
            
            // �����ϴδ洢��ֵ
            last_stored_grind_time = current_grind_time;
            
            // ����ı��־
            grind_time_changed = 0;
            
            // ��Flash�������ʱ�䣨��ѡ��
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        
        // ������ʱ������CPUռ��
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}*/