#include "flash.h"
#include <string.h>
#include "FreeRTOS.h"
#include <stdio.h>
#include "stdint.h"
#include "protocol.h"

GrindData GrindSetData ;
extern volatile uint16_t volume;
void flashDataInit(void) 
{
    ///read flash data
    getGrindDataFromFlash();
    if (GrindSetData.time_1 == 0xFFFFFFFF) {
        ///write default data
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<10;j++)
            {
                GrindSetData.extract_time[i][j]=0;
            }
        }
        GrindSetData.time_1 = 15;
        GrindSetData.time_2 = 20;
        GrindSetData.time_3 = 30;
        GrindSetData.steamtime = 10;
        GrindSetData.temp_steam = 125;
        GrindSetData.temp_coffee = 92;
        GrindSetData.time_hotwater = 0;
        GrindSetData.temp_brew = 92;
        GrindSetData.password = 9999;
        flashDataSave();
    }

}

void flashDataSave(void)
{
    FLASH_WriteData(
        USER_FLASH_DATA_ADDR,
        (uint32_t *)&GrindSetData,
        (sizeof(GrindSetData)+3)/4
    );
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
    memcpy(
        &GrindSetData,
        (void *)USER_FLASH_DATA_ADDR,
        sizeof(GrindSetData)
    );
}

