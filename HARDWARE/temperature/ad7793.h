#ifndef __AD7793_H__
#define __AD7793_H__

#include "sys.h"


#define AD7793_SCLK_H HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET)
#define AD7793_SCLK_L HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET)

#define AD7793_CS_H HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET)
#define AD7793_CS_L HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET)

#define AD7793_SDI_H HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET)
#define AD7793_SDI_L HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET)

#define AD7793_DOUT HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)

void GPIO_Configuration(void);
void AD7793_thermocouple_init(void);//初始化热电偶通道
void AD7793_GetPT100_init(void);//初始化PT100通道
float Get_PT100(void);//读取PT100温度值，返回值为温度值
float Get_thermocouple_Value(void);//读取热电偶通道，返回值为热电势
void AD7793init(void);
uint8_t Get_AD7793_ID(void);

double kTypeVoltage2Temperature(double voltage);
double kTypeTemperature2Voltage(double input_temp);

#endif
