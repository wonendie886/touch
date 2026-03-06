#ifndef __UART_H
#define __UART_H

#include "stm32f4xx_hal.h"
#include "stdint.h"

void uart4_init(void);
void uart6_init(void);

uint32_t sendData(const void* buf, uint32_t len);

#endif /* __UART_H */
