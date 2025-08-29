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
void grind_time_init(void) {
    uint32_t saved_time;
    int ret = FLASH_LoadConfig(&saved_time);
    
    if (ret == 1) {
        // �ɹ����ر����ʱ��
        current_grind_time = saved_time;
        //printf("��Flash������ĥʱ��: %d\n", current_grind_time);
    } else if (ret == 0) {
        // û����Ч���ݣ�ʹ��Ĭ��ֵ
        current_grind_time = 10;
        //printf("ʹ��Ĭ����ĥʱ��: %d\n", current_grind_time);
    } else {
        // CRCУ��ʧ�ܣ�ʹ��Ĭ��ֵ
        current_grind_time = 10;
       // printf("CRCУ��ʧ�ܣ�ʹ��Ĭ����ĥʱ��: %d\n", current_grind_time);
    }
}

UART_HandleTypeDef huart6;

// USART6初始化函数
static void MX_USART6_UART_Init(void)
{
    // 1. 使能USART6时钟
    __HAL_RCC_USART6_CLK_ENABLE();
    // 2. 使能GPIOC时钟（PC6所在端口）
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // 3. 配置PC6为USART6_TX
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;        // 复用推挽输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;   // 复用功能8 = USART6
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // 4. 配置USART6参数
    huart6.Instance = USART6;
    huart6.Init.BaudRate = 115200;
    huart6.Init.WordLength = UART_WORDLENGTH_8B;
    huart6.Init.StopBits = UART_STOPBITS_1;
    huart6.Init.Parity = UART_PARITY_NONE;
    huart6.Init.Mode = UART_MODE_TX;               // 仅发送模式
    huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart6.Init.OverSampling = UART_OVERSAMPLING_16;
    
    // 5. 初始化USART6
    if (HAL_UART_Init(&huart6) != HAL_OK)
    {
    }
}
// 重定向printf到USART6
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
    /*
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
    */
}

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
	//uart_init(115200);             	//��ʼ��USART
	usmart_dev.init(84); 		        //��ʼ��USMART
	LED_Init();										//��ʼ��LED
	TIM2_Init();							  // ��ʼ��TIM2		
	//KEY_Init();						          //��ʼ��KEY
    MX_USART6_UART_Init(); 

    nv3401_gpio_init();
    nv3401_lcd_init();

    //lcd_read_id();
    printf("Hello World t!\r\n");
	//LCD_Init();								  // ��ʼ��LCD
//	//Modbus_Init(9600); // ��ʼ��Modbus
//	//grind_time_init();     //��ʼ��ʱ��			   
	//tp_dev.init();				          //��������ʼ�� 
//	
	//lv_init();
	//lv_port_disp_init();   // ��Ҫʵ�ֵ���ʾ�ӿ�
	//lv_port_indev_init();  // ��Ҫʵ�ֵĴ��ؽӿ�
	// ��ʼ��UI������������������
	//setup_ui(&guider_ui);
	//events_init(&guider_ui);

	xTaskCreate(vLCD_Refresh_LED_Task,"lcd_refresh_led_task",256,NULL,1,&xLCD_Refresh_LED_TaskHandle);
	//xTaskCreate(vLvglTaskFunction,"lvgl_task",4096,NULL,3,&xLvglTaskHandle);
	//xTaskCreate(vflash, "flash_task", 1024, NULL, 2, &xFlashTaskHandle);
	vTaskStartScheduler();  //����������������ʼִ��

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
	const TickType_t xPeriod2 = pdMS_TO_TICKS( 100 );  //��������ֵ    5ms
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
}