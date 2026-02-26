#include "modbus.h"
#include "led.h"
#include "flash.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "protocol.h"


UART_HandleTypeDef huart4;

static uint8_t rx_data = 0;

void uart4_init(void)
{ 
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    huart4.Instance = UART4;
    huart4.Init.BaudRate = 115200;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX; 
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_8;
    
    if (HAL_UART_Init(&huart4) != HAL_OK){
        printf("uart4 init error");
    }

    ///enable receive interrupt
    HAL_UART_Receive_IT(&huart4, &rx_data, 1);
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(uartHandle->Instance == UART4) {
        __HAL_RCC_UART4_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;       
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4; 
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_1;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;       
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitTypeDef gpio_initure = {0};
        
        gpio_initure.Pin = GPIO_PIN_2;	
        gpio_initure.Mode = GPIO_MODE_OUTPUT_PP;  
        gpio_initure.Pull = GPIO_PULLUP;          //GPIO_NOPULL
        gpio_initure.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_initure); 

        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);

        HAL_NVIC_SetPriority(UART4_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
    }
}


void UART4_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart4);
}

uint8_t rFrameBuf[FRAME_MAX_LEN];

volatile uint8_t dataIsReady = 0;

static uint8_t frameLen = 0;
static uint8_t rxStatus = 0;
uint8_t recivedCount = 0;
static uint8_t redata = 0;

enum _STATUS{
    RX_NULL = 0,
    RX_HEAD,
    RX_RECIVE_LEN,
    RX_ING,
};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == UART4)
    {
        LED0 = !LED0;
        
        redata = rx_data;
        if (dataIsReady == 0) {
            if (rxStatus == RX_NULL){
                if (redata == FRAME_HEAD_1){
                    recivedCount = 0;
                    rxStatus = RX_HEAD;
                    rFrameBuf[recivedCount++] = redata;
                }
            } else if (rxStatus == RX_HEAD) {
                if (redata == FRAME_HEAD_2){
                    rFrameBuf[recivedCount++] = redata;
                    rxStatus = RX_RECIVE_LEN;
                } else {
                    rxStatus = RX_NULL;
                }
            } else if (rxStatus == RX_RECIVE_LEN) {
				rFrameBuf[recivedCount++] = redata;
				frameLen = redata;
				rxStatus = RX_ING;
                //printf("len = %d\n", frameLen);
			} else if(rxStatus == RX_ING) {

				if (recivedCount >= FRAME_MAX_LEN){
					rxStatus = RX_NULL;
				} else {
					rFrameBuf[recivedCount++] = redata;

					if (recivedCount == frameLen ){
						dataIsReady = 1; 
						rxStatus = RX_NULL;
					}
				}
			}
		}

        HAL_UART_Receive_IT(&huart4, &rx_data, 1);
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == UART4)
    {
        printf("UART4 HAL_UART_ErrorCallback\n");
        // 清除错误标志
        __HAL_UART_CLEAR_PEFLAG(huart);  // 清除奇偶校验错误
        __HAL_UART_CLEAR_FEFLAG(huart);  // 清除帧错误
        __HAL_UART_CLEAR_NEFLAG(huart);  // 清除噪声错误
        __HAL_UART_CLEAR_OREFLAG(huart); // 清除溢出错误
        
        // 复位状态
        rxStatus = RX_NULL;
        recivedCount = 0;
        
        // 重新启动接收
        HAL_UART_Receive_IT(&huart4, &rx_data, 1);
    }
}


uint32_t sendData(const void* buf, uint32_t len)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);

    if(HAL_UART_Transmit(&huart4, (uint8_t *)buf, len, 100) != HAL_OK) {
        len = 0;
    }

    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
    return len;
}

TIM_HandleTypeDef htim3;
void timer3_init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 4199;                  // 84MHz / (4199+1) = 20kHz (50us计数)
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 80;                       // 初始值70*50us=3.5ms @9600bps
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
    }

    __HAL_TIM_SET_COUNTER(&htim3, 0);
    HAL_TIM_Base_Stop_IT(&htim3);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{
    if(tim_baseHandle->Instance == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);  
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }
}

void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3) {
    } else if(htim->Instance == TIM2) {
        HAL_IncTick();
    }
}

static void timerStop(void)
{
    HAL_TIM_Base_Stop_IT(&htim3);
}

static void timerStart(void)
{
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    HAL_TIM_Base_Start_IT(&htim3);
}