#ifndef __MODBUS_H
#define __MODBUS_H

#include "mbrtu_master.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"

void modbus_init(void);
void modbus_test(void);
uint32_t sendData(const void* buf, uint32_t len);


extern MBRTUMaterTypeDef MbRtu;

#endif /* __MODBUS_H */
