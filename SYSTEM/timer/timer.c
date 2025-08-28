#include "timer.h"
#include "lvgl.h"
#include "flash.h"
TIM_HandleTypeDef htim2;

/**
  * @brief  定时器2配置 (1ms 触发一次中断)
  * @note   基于 HAL，完全独立，不依赖 CubeMX
  */
void TIM2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();   // 使能 TIM2 时钟

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 84 - 1;              // 分频 (84MHz/84 = 1MHz, 1us)
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000 - 1;               // 自动重装载值 (1000 * 1us = 1ms)
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        while(1); // 需要用户实现 Error_Handler()
    }

    /* 开启定时器中断 */
    HAL_TIM_Base_Start_IT(&htim2);

    /* 配置 NVIC */
    HAL_NVIC_SetPriority(TIM2_IRQn, 10, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

/**
  * @brief  TIM2 中断入口函数
  */
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}

/**
  * @brief  HAL 定时器更新回调函数
  * @note   1ms 触发一次，驱动 LVGL 心跳
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        HAL_IncTick();
        //lv_tick_inc(1);
    }
}
