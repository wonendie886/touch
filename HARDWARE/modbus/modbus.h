#ifndef __MODBUS_H
#define __MODBUS_H

#include "mbrtu_master.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"

void modbus_init(void);
void modbus_test(void);


extern MBRTUMaterTypeDef MbRtu;

#endif /* __MODBUS_H */
