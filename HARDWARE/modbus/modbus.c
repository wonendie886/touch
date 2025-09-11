#include "modbus.h"
#include "led.h"
#include "flash.h"
#ifdef 0
static void mutex_lock(void);
static void mutex_unlock(void);
#endif
static void timerStop(void);
static void timerStart(void);
static void delayms(uint32_t nms);
static uint32_t sendData(const void* buf, uint32_t len);


UART_HandleTypeDef huart4;
TIM_HandleTypeDef htim3;

MBRTUMaterTypeDef MbRtu =
{
    .delayms                      = delayms,
    .timerStart                   = timerStart,
    .timerStop                    = timerStop,
    .sendData                     = sendData,

#ifdef 0
    .lock                         = mutex_lock,
    .unlock                       = mutex_unlock,
#endif
};

static uint8_t rx_data = 0;

void uart4_init(void)
{ 
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    huart4.Instance = UART4;
    huart4.Init.BaudRate = 9600;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX; 
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&huart4) != HAL_OK){
        
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
        GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;       
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4; 
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitTypeDef gpio_initure = {0};
        
        gpio_initure.Pin = GPIO_PIN_2;	
        gpio_initure.Mode = GPIO_MODE_OUTPUT_PP;  
        gpio_initure.Pull = GPIO_PULLUP;          //GPIO_NOPULL
        gpio_initure.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(GPIOA,&gpio_initure); 

        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);

        HAL_NVIC_SetPriority(UART4_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
    }
}


void UART4_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart4);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == UART4)
    {
        MBRTUMasterRecvByteISRCallback(&MbRtu,rx_data);
        HAL_UART_Receive_IT(&huart4, &rx_data, 1);
    }
}

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
        MBRTUMasterTimerISRCallback(&MbRtu);
    } else if(htim->Instance == TIM2) {
        HAL_IncTick();
    }
}

void modbus_init(void)
{
    uart4_init();

    timer3_init();	
}

#ifdef 0

static void mutex_lock(void)
{

}

static void mutex_unlock(void)
{

}

#endif

static void timerStop(void)
{
    HAL_TIM_Base_Stop_IT(&htim3);
}

static void timerStart(void)
{
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    HAL_TIM_Base_Start_IT(&htim3);
}

static void delayms(uint32_t nms)
{
    HAL_Delay(nms);
}

static uint32_t sendData(const void* buf, uint32_t len)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
    

    if(HAL_UART_Transmit(&huart4, (uint8_t *)buf, len, 100) != HAL_OK) {
        len = 0;
    }

    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
    return len;
}

void modbus_test(void)
{

    int ret = 0;
    uint16_t usBuf[10] = {0};
     ret = MBRTUMasterReadHoldingRegisters(&MbRtu, 1, 0, 4, 100, usBuf);
    HAL_Delay(100);
//    // 写多个寄存器
//    memset(usBuf, 0XFF, 20);
//    ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 1, 0, 8, usBuf, 500);
//    printf(" write regs %s. \r\n", ret < 0 ? "failed" : "ok");

//    HAL_Delay(100);


//    ret = MBRTUMasterReadHoldingRegisters(&MbRtu, 1, 0, 4, 100, usBuf);
//    printf(" read hold regs %s. \r\n", ret < 0 ? "failed" : "ok");
//    if (ret >= 0){
//        for(int i = 0; i < 4; i++)
//            printf("reg[%d] = %d \r\n", i, usBuf[i]);
//    }

//    memset(usBuf, 0XBB, 20);
//    ret = MBRTUMasterWriteMultipleRegisters(&MbRtu, 1, 0, 2, usBuf, 500);
//    printf(" write regs %s. \r\n", ret < 0 ? "failed" : "ok");

//    HAL_Delay(100);
//    ret = MBRTUMasterReadHoldingRegisters(&MbRtu, 1, 0, 4, 100, usBuf);
//    printf(" read hold regs %s. \r\n", ret < 0 ? "failed" : "ok");
//    if (ret >= 0){
//        for(int i = 0; i < 4; i++)
//            printf("reg[%d] = %d \r\n", i, usBuf[i]);
//    }
//    HAL_Delay(100);
//    
//    
//    ret = MBRTUMasterWriteSingleRegister(&MbRtu, 0x01, INDEX_GRIND_ENABLE, 1, 100);

//    printf(" 1111111 write regs %s. \r\n", ret < 0 ? "failed" : "ok");
}