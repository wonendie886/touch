#include "flash.h"
#include <string.h>
#include "FreeRTOS.h"
#include <stdio.h>
#include "stdint.h"
#include "protocol.h"
#include "events_init.h"

GrindData GrindSetData ;
extern struct GrindRealData GrindDataStr;
void flashDataInit(void) 
{
    loadCustomDataFromFlash();
}

void flashDataSave(void)
{
    uint32_t buffer[8] = {0};
    buffer[0] = GrindSetData.time_1;
    buffer[1] = GrindSetData.time_2;
    buffer[2] = GrindSetData.time_3;
    buffer[3] = GrindSetData.weight_1;
    buffer[4] = GrindSetData.weight_2;
    buffer[5] = GrindSetData.weight_3;
    buffer[6] = GrindSetData.grind_mode;
    buffer[7] = GrindSetData.grind_thickness;
    //printf("BUFFER[0] == %d\n",buffer[0]);
    FLASH_WriteData(USER_FLASH_DATA_ADDR, buffer, sizeof(buffer) / sizeof(buffer[0]));
}

// 新增：保存自定义数据到Flash
void saveCustomDataToFlash(void)
{
    uint32_t buffer[5] = {0}; // 存储GrindDataStr.data.target(1个) + TimeDataStr的3个字段共4个值，加1个校验值
    buffer[0] = GrindDataStr.data.target;  // GrindDataStr.data.target
    buffer[1] = TimeDataStr.time1;         // TimeDataStr.time1
    buffer[2] = TimeDataStr.time2;         // TimeDataStr.time2
    buffer[3] = TimeDataStr.time3;         // TimeDataStr.time3
    buffer[4] = 0xDEADBEEF;               // 校验值，用于确认数据有效

    FLASH_WriteData(USER_FLASH_DATA_ADDR, buffer, sizeof(buffer) / sizeof(buffer[0]));
}

// 新增：从Flash加载自定义数据
void loadCustomDataFromFlash(void)
{
    uint32_t buffer[5] = {0};
    uint32_t *src = (uint32_t*)USER_FLASH_DATA_ADDR;
    uint32_t size = sizeof(buffer) / sizeof(buffer[0]);

    for (uint32_t i = 0; i < size; i++) {
        buffer[i] = src[i];
    }

    // 检查校验值是否匹配，确保数据有效性
    if (buffer[4] == 0xDEADBEEF) {
        GrindDataStr.data.target = buffer[0];
        TimeDataStr.time1 = (uint8_t)buffer[1];
        TimeDataStr.time2 = (uint8_t)buffer[2];
        TimeDataStr.time3 = (uint8_t)buffer[3];
    } else {
        // 如果数据无效，使用默认值
        GrindDataStr.data.target = 125; // 默认3秒
        TimeDataStr.time1 = 30;          // 默认值
        TimeDataStr.time2 = 45;          // 默认值
        TimeDataStr.time3 = 60;          // 默认值
        // 并保存默认值到Flash
        saveCustomDataToFlash();
    }

    printf("time_1: %d\n", TimeDataStr.time1);
    printf("time_2: %d\n", TimeDataStr.time2);
    printf("time_3: %d\n", TimeDataStr.time3);
    printf("target: %d\n", GrindDataStr.data.target);
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
    uint32_t buffer[8] = {0};

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

