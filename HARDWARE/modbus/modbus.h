#ifndef __MODBUS_H
#define __MODBUS_H

#include "stm32f4xx_hal.h"
#include "stdint.h"

uint32_t sendData(const void* buf, uint32_t len);



#endif /* __MODBUS_H */
