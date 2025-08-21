#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f4xx.h"  // 直接使用寄存器头文件
#include "stdint.h"     // 用到的类型

#define GRIND_TIME_ADDR 0x080C0000  // Sector 11基地址
#define FLASH_SECTOR    FLASH_SECTOR_11

typedef struct {
  uint32_t checksum;
  uint32_t grind_time_s;
} GrindConfig_t;

void FLASH_StoreConfig(uint32_t grind_time);
int FLASH_LoadConfig(uint32_t *saved_time);

#endif