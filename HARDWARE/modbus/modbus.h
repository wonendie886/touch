#ifndef __MODBUS_H
#define __MODBUS_H

#include "stm32f4xx_hal.h"
#include "stdint.h"
// 硬件定义
#define MODBUS_UART        USART2
#define MODBUS_DE_GPIO     GPIOA
#define MODBUS_DE_PIN      GPIO_PIN_2

void uart4_init(void);
void UART_SendData(char *data, int len);

// 接口函数
void Modbus_Init(uint32_t baudrate);
void Modbus_Send(uint8_t *pData, uint16_t Size);
uint16_t Modbus_CRC16(uint8_t *buf, uint16_t len);

// 新增：发送磨豆时间指令
void Modbus_SendGrindTime(uint8_t cup_size);
#endif /* __MODBUS_H */
