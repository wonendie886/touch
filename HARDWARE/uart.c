#include "uart.h"
#include "led.h"
#include "protocol.h"

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart6;

static uint8_t rx_data = 0;

void uart4_init(void)
{ 
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

    HAL_NVIC_SetPriority(UART4_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
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
                        // for(int i=0;i<frameLen;i++)
                        // {
                        //     printf("%02X ",rFrameBuf[i]);
                        // }
                        // printf("\n");                        
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
        // 读取状态寄存器
        uint32_t error_code = huart->ErrorCode;
        uint32_t sr_register = UART4->SR;  // 直接读取状态寄存器
        
        // 打印错误信息（如果可以使用printf）
        printf("UART4 Error! ErrorCode: 0x%08lX, SR: 0x%04lX\r\n", error_code, sr_register);
        
        // 检查具体错误位
        if (error_code & HAL_UART_ERROR_PE) {
            printf("  - Parity Error\r\n");  // 奇偶校验错误
        }
        if (error_code & HAL_UART_ERROR_NE) {
            printf("  - Noise Error\r\n");    // 噪声错误
        }
        if (error_code & HAL_UART_ERROR_FE) {
            printf("  - Frame Error\r\n");    // 帧错误
        }
        if (error_code & HAL_UART_ERROR_ORE) {
            printf("  - Overrun Error\r\n");  // 溢出错误
        }
        if (error_code & HAL_UART_ERROR_DMA) {
            printf("  - DMA Error\r\n");      // DMA错误
        }
        // 清除错误标志
        __HAL_UART_CLEAR_PEFLAG(huart);  // 清除奇偶校验错误
        __HAL_UART_CLEAR_FEFLAG(huart);  // 清除帧错误
        __HAL_UART_CLEAR_NEFLAG(huart);  // 清除噪声错误
        __HAL_UART_CLEAR_OREFLAG(huart); // 清除溢出错误
        
        // // 复位状态
        rxStatus = RX_NULL;
        recivedCount = 0;
        
        // // 重新启动接收
        HAL_UART_Receive_IT(&huart4, &rx_data, 1);
    }
}

uint32_t sendData(const void* buf, uint32_t len)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
    for(int k = 0; k < 6000; k++)
        ;
    if(HAL_UART_Transmit_IT(&huart4, (uint8_t *)buf, len) != HAL_OK) {
        len = 0;
    }
    for(int k = 0; k < 200000; k++)
        ;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
    return len;
}

// USART6初始化函数
void uart6_init(void)
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