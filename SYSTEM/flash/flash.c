#include "flash.h"
#include <string.h>
#include "FreeRTOS.h"
#include <stdio.h>
#include "stdint.h"

GrindData GrindSetData ;

/* 计数页空闲槽游标（RAM）：扇区擦除后由 flashDataSave 清零 */
static uint32_t cupPageNext = 0;

void flashDataInit(void)
{
    ///read flash data
    getGrindDataFromFlash();

    /* 老固件的 Flash 布局没有杯数字段，升级后会读到擦除值 0xFFFFFFFF，清零处理 */
    if (GrindSetData.single_cups == 0xFFFFFFFF) {
        GrindSetData.single_cups = 0;
    }
    if (GrindSetData.double_cups == 0xFFFFFFFF) {
        GrindSetData.double_cups = 0;
    }

    ///扫描计数页，累加自上次设置保存以来的杯数事件
    cupCounterInit();

    if (GrindSetData.time_1 == 0xFFFFFFFF) {
        ///write default data
        GrindSetData.time_1 = 3000;
        GrindSetData.time_2 = 6000;
        GrindSetData.time_3 = 5000;
        GrindSetData.weight_1 = 160;
        GrindSetData.weight_2 = 180;
        GrindSetData.weight_3 = 190;
        GrindSetData.grind_mode = MODE_TIME;

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
    buffer[7] = GrindSetData.single_cups;
    buffer[8] = GrindSetData.double_cups;

    //printf("BUFFER[0] == %d\n",buffer[0]);
    FLASH_WriteData(USER_FLASH_DATA_ADDR, buffer, sizeof(buffer) / sizeof(buffer[0]));

    /* 整扇区擦除后计数页已清空，游标归零 */
    cupPageNext = 0;

    printf("[flash] settings saved, page reset | s=%lu d=%lu\r\n",
           (unsigned long)GrindSetData.single_cups,
           (unsigned long)GrindSetData.double_cups);
}

/* 上电扫描计数页：累加自上次设置保存以来的杯数事件
   事件字编码：0=单杯 1=双杯 2=手动 */
void cupCounterInit(void)
{
    uint32_t *p = (uint32_t *)CUP_COUNTER_ADDR;

    for (cupPageNext = 0; cupPageNext < CUP_COUNTER_SIZE_WORDS; cupPageNext++) {
        uint32_t v = p[cupPageNext];
        if (v == 0xFFFFFFFF) {
            break;              /* 空闲槽，页尾 */
        }
        if (v == 0x00000000) {
            GrindSetData.single_cups++;
        } else if (v == 0x00000001) {
            GrindSetData.double_cups++;
        } else if (v == 0x00000002) {
            continue;           /* 旧固件的手动杯事件：跳过不计 */
        } else {
            break;              /* 损坏数据，停止扫描 */
        }
    }

    printf("[cup] init scan: page events=%lu | s=%lu d=%lu\r\n",
           (unsigned long)cupPageNext,
           (unsigned long)GrindSetData.single_cups,
           (unsigned long)GrindSetData.double_cups);
}

/* 记录一杯：写一个事件字（1->0 位写，无需擦除），并同步 RAM 计数
   cupType: 0=单杯 1=双杯 2=手动 */
void cupCounterRecord(uint8_t cupType)
{
    HAL_StatusTypeDef st;
    uint32_t slot = cupPageNext;
    uint32_t addr;
    uint32_t prev;
    uint32_t sr_before;

    /* 计数页写满：先把累计吸收进设置区（整扇区擦除重写，页随之清空） */
    if (cupPageNext >= CUP_COUNTER_SIZE_WORDS) {
        printf("[cup] page full, absorb to settings\r\n");
        flashDataSave();
        slot = cupPageNext;
    }

    addr = CUP_COUNTER_ADDR + slot * 4;
    prev = *(volatile uint32_t *)addr;
    sr_before = FLASH->SR;

    /* 该 HAL 版本的坑：
       1. Unlock 在“已解锁”时返回 HAL_ERROR；
       2. FLASH->SR 错误标志不会自清，残留标志会让 Program 的入口检查直接失败。
       对策：先清全部错误标志；解锁失败则强制加锁后重新解锁，保证写路径幂等 */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    st = HAL_FLASH_Unlock();
    if (st != HAL_OK) {
        HAL_FLASH_Lock();
        st = HAL_FLASH_Unlock();
    }

    if (st == HAL_OK) {
        st = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, (uint32_t)cupType);
        HAL_FLASH_Lock();
    }

    /* 成功或失败都推进游标：失败时跳过坏槽位，避免后续事件永远卡在同一槽 */
    cupPageNext++;

    if (cupType == 1) {
        GrindSetData.double_cups++;
    } else {
        GrindSetData.single_cups++;
    }

    printf("[cup] write type=%u addr=0x%08lX slot=%lu prev=0x%08lX sr=0x%08lX st=%d | ram total s=%lu d=%lu\r\n",
           (unsigned)cupType, (unsigned long)addr, (unsigned long)slot,
           (unsigned long)prev, (unsigned long)sr_before, (int)st,
           (unsigned long)GrindSetData.single_cups,
           (unsigned long)GrindSetData.double_cups);
}

/* 读取 Flash 中真实杯数（设置区基准 + 计数页事件），只读不修改 RAM 计数 */
void cupCounterReadFromFlash(uint32_t *single, uint32_t *double_cups)
{
    uint32_t i;
    uint32_t *settings = (uint32_t *)USER_FLASH_DATA_ADDR;
    uint32_t *page = (uint32_t *)CUP_COUNTER_ADDR;

    /* 基准：设置区第 8、9 个字（老数据为擦除值时按 0 处理） */
    uint32_t s = settings[7];
    uint32_t d = settings[8];
    if (s == 0xFFFFFFFF) {
        s = 0;
    }
    if (d == 0xFFFFFFFF) {
        d = 0;
    }

    /* 累加计数页内未被吸收的事件 */
    for (i = 0; i < CUP_COUNTER_SIZE_WORDS; i++) {
        uint32_t v = page[i];
        if (v == 0xFFFFFFFF) {
            break;
        }
        if (v == 0x00000000) {
            s++;
        } else if (v == 0x00000001) {
            d++;
        } else if (v == 0x00000002) {
            continue;           /* 旧固件的手动杯事件：跳过不计 */
        } else {
            break;
        }
    }

    *single = s;
    *double_cups = d;

    printf("[cup] read flash: base s=%lu d=%lu + page events=%lu | total s=%lu d=%lu\r\n",
           (unsigned long)settings[7] == 0xFFFFFFFF ? 0UL : (unsigned long)settings[7],
           (unsigned long)settings[8] == 0xFFFFFFFF ? 0UL : (unsigned long)settings[8],
           (unsigned long)i,
           (unsigned long)s, (unsigned long)d);
}

#if CUP_COUNTER_TEST
/* 测试用：直接向计数页写入 n 个事件，绕过研磨流程。
   事件值用 0x02（扫描/读取都会跳过不计），只占槽位不污染计数，
   用于模拟计数页写满，验证吸收逻辑 */
void cupCounterTestFill(uint32_t n)
{
    uint32_t i;
    printf("[cup] test fill begin, page=%lu\r\n", (unsigned long)cupPageNext);
    HAL_FLASH_Unlock();
    for (i = 0; i < n && cupPageNext < CUP_COUNTER_SIZE_WORDS; i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,
                              CUP_COUNTER_ADDR + cupPageNext * 4,
                              0x00000002UL) != HAL_OK) {
            break;
        }
        cupPageNext++;
    }
    HAL_FLASH_Lock();
    printf("[cup] test fill done: %lu events written\r\n", (unsigned long)i);
}
#endif

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
    GrindSetData.single_cups = buffer[7];
    GrindSetData.double_cups = buffer[8];

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

