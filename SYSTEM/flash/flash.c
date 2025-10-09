#include "flash.h"
#include <string.h>
#include "FreeRTOS.h"
#include <stdio.h>
#include "stdint.h"

GrindData GrindSetData ;

void flashDataInit(void) 
{
    ///read flash data
    getGrindDataFromFlash();

    if (GrindSetData.time_1 == 0xFFFFFFFF) {
        ///write default data
        GrindSetData.time_1 = 5000;
        GrindSetData.time_2 = 6000;
        GrindSetData.time_3 = 7000;
        GrindSetData.weight_1 = 160;
        GrindSetData.weight_2 = 180;
        GrindSetData.weight_3 = 190;
        GrindSetData.grind_mode = MODE_TIME;
        GrindSetData.grind_thickness = 300;
        flashDataSave();
    }

}

void flashDataSave(void)
{
    uint32_t buffer[9] = {0};
    buffer[0] = GrindSetData.time_1;
    buffer[1] = GrindSetData.time_2;
    buffer[2] = GrindSetData.time_3;
    buffer[3] = GrindSetData.weight_1;
    buffer[4] = GrindSetData.weight_2;
    buffer[5] = GrindSetData.weight_3;
    buffer[6] = GrindSetData.grind_mode;
    buffer[7] = GrindSetData.grind_thickness;
    buffer[8] = GrindSetData.grind_speed;
    //printf("BUFFER[0] == %d\n",buffer[0]);
    FLASH_WriteData(USER_FLASH_DATA_ADDR, buffer, sizeof(buffer) / sizeof(buffer[0]));
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

    status = HAL_FLASH_Unlock();
    if (status != HAL_OK) {
        return status;
    }

    /* 2. 清除所有错误标志位 (可选，但推荐) */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    FLASH_EraseSector(USER_FLASH_SECTOR);

    /* 循环写入每一个字 */
    for (i = 0; i < Size; i++) {
        status = FLASH_WriteWord(WriteAddr, pData[i]);
        if (status != HAL_OK) {
            break; // 如果写入失败，跳出循环
        }
        WriteAddr += 4; // 地址递增4字节
    }

    HAL_FLASH_Lock();

    return status;
}

void getGrindDataFromFlash() 
{
    uint32_t buffer[9] = {0};

    uint32_t *src = (uint32_t*)USER_FLASH_DATA_ADDR;

    uint32_t size = sizeof(buffer) / sizeof(buffer[0]);
    for (uint32_t i = 0; i < size; i++) {
        buffer[i] = src[i];
    }

    GrindSetData.time_1 = buffer[0];
    GrindSetData.time_2 = buffer[1];
    GrindSetData.time_3 = buffer[2];
    GrindSetData.weight_1 = buffer[3];
    GrindSetData.weight_2 = buffer[4];
    GrindSetData.weight_3 = buffer[5];
    GrindSetData.grind_mode = buffer[6];
    GrindSetData.grind_thickness = buffer[7]; 
    GrindSetData.grind_speed = buffer[8];
    /*
    printf("time_1: %d\n", GrindSetData.time_1);
    printf("time_2: %d\n", GrindSetData.time_2);
    printf("time_3: %d\n", GrindSetData.time_3);
    printf("weight_1: %d\n", GrindSetData.weight_1);
    printf("weight_2: %d\n", GrindSetData.weight_2);
    printf("weight_3: %d\n", GrindSetData.weight_3);
    printf("grind_mode: %d\n", GrindSetData.grind_mode);
    */
}

