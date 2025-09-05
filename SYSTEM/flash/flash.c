/* flash_task.c - Flash storage task for STM32F407 (halfword programming)
 *
 * Requires:
 *  - FreeRTOS V10.5.1
 *  - CMSIS core headers (for NVIC, __disable_irq etc.)
 *  - Ensure the ramfunc placement macro is handled by linker (see notes)
 *
 * This file uses direct register access for FLASH on STM32F4.
 */

#include "flash.h"
#include <string.h>
#include "FreeRTOS.h"
#include <stdio.h>
#include "stdint.h"



HAL_StatusTypeDef FLASH_Init(void) {
    HAL_StatusTypeDef status;

    /* 1. 解锁Flash */
    status = HAL_FLASH_Unlock();
    if (status != HAL_OK) {
        return status;
    }

    /* 2. 清除所有错误标志位 (可选，但推荐) */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    return HAL_OK;
}


uint32_t FLASH_ReadWord(uint32_t Address) {
    /* 通过指针直接访问内存地址 */
    return (*(__IO uint32_t*) Address);
}


HAL_StatusTypeDef FLASH_EraseSector(uint32_t Sector) {
    HAL_StatusTypeDef status;
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t SectorError = 0;

    /* 配置擦除参数 */
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3; // 电压范围，适用于3.3V系统
    EraseInitStruct.Sector = Sector; // 起始扇区
    EraseInitStruct.NbSectors = 1;   // 要擦除的扇区数量

    /* 执行擦除操作 */
    status = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
    return status;
}


HAL_StatusTypeDef FLASH_WriteWord(uint32_t Address, uint32_t Data) {
    HAL_StatusTypeDef status;

    /* 执行编程操作，使用字编程模式 */
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data);
    return status;
}


HAL_StatusTypeDef FLASH_WriteData(uint32_t Address, uint32_t *pData, uint32_t Size) {
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t i;
    uint32_t WriteAddr = Address;

    /* 循环写入每一个字 */
    for (i = 0; i < Size; i++) {
        status = FLASH_WriteWord(WriteAddr, pData[i]);
        if (status != HAL_OK) {
            break; // 如果写入失败，跳出循环
        }
        WriteAddr += 4; // 地址递增4字节
    }

    return status;
}


void flash_store_read(flash_store_t *store) {
    uint32_t *src = (uint32_t*)USER_FLASH_START_ADDR;
    uint32_t *dst = (uint32_t*)store;
    uint32_t size = sizeof(flash_store_t) / 4; // 除以4，因为每次读取4字节
    for (uint32_t i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

void flash_store_write(flash_store_t *store) {
    // 擦除扇区
    FLASH_EraseSector(USER_FLASH_SECTOR);
    
    // 写入数据
    uint32_t *src = (uint32_t*)store;
    uint32_t *dst = (uint32_t*)USER_FLASH_START_ADDR;
    uint32_t size = sizeof(flash_store_t) / 4;
    for (uint32_t i = 0; i < size; i++) {
        FLASH_WriteWord((uint32_t)&dst[i], src[i]);
    }
}