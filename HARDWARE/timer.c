#include "timer.h"

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