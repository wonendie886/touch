#ifndef __TIMER_H
#define __TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/* TIM2 句柄对外声明 */
extern TIM_HandleTypeDef htim2;

/* 初始化函数 */
void TIM2_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */
