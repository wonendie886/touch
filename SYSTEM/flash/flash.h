#ifndef FLASH_H
#define FLASH_H

#include "stm32f4xx_hal.h"  // 确保已包含HAL库头文件
#include "stdbool.h"
typedef enum _INPUT_REG_OFFSET{
    INDEX_GRIND_MOTOR_RUNNING = 0,
    INDEX_GRIND_DATA,
    INDEX_STEP_MOTOR_RUNNING,
    INDEX_STEP_DATA,
}INPUT_REG_OFFSET;

typedef enum _HOLDING_REG_OFFSET{
    INDEX_GRIND_ENABLE = 0,
    INDEX_GRIND_MODE,
    INDEX_GRIND_TIME,
    INDEX_GRIND_WEIGHT,
    INDEX_GRIND_RESET,
    INDEX_STEP_ENABLE,
    INDEX_STEP_DIR,
    INDEX_STEP_MODE,
    INDEX_STEP_TIME,
} HOLDING_REG_OFFSET;

enum _GRIND_MODE{
    MODE_TIME = 0,
    MODE_WEIGHT,
};
enum _STEP_MODE{
    MODE_COARSE,
    MODE_FINE,
};

enum _GRIND_STATUS{
    STATUS_IN_GRIND_STOP = 0,
    STATUS_IN_GRIND_START,
};


extern bool isGrindMode;

/* 根据你的芯片型号定义Flash大小和起始地址 */
#define STM32_FLASH_BASE        0x08000000UL    /* STM32 Flash的起始地址 */
#define STM32_FLASH_SIZE        (512 * 1024)    /* STM32F407VET6 的Flash大小为512KB */
#define FLASH_END_ADDRESS       (STM32_FLASH_BASE + STM32_FLASH_SIZE)


#define USER_FLASH_DATA_ADDR   0x08004000      /* Sector 1 */
#define USER_FLASH_SECTOR       FLASH_SECTOR_1  /* 对应扇区编号 */
#define MAX_TEXT_LEN  8
typedef struct {
    char label1_text[MAX_TEXT_LEN];
    char label2_text[MAX_TEXT_LEN];
    char label3_text[MAX_TEXT_LEN];
    char label4_text[MAX_TEXT_LEN];
    char label5_text[MAX_TEXT_LEN];
    char label6_text[MAX_TEXT_LEN];

} flash_store_t;

typedef struct _GRIND_DATA{
    uint32_t time_1;    // unit: ms
    uint32_t time_2;
    uint32_t time_3;
    uint32_t weight_1;  // unit: g  scale:10
    uint32_t weight_2;
    uint32_t weight_3;
    uint32_t grind_mode;    //weight or time
} GrindData;

extern volatile uint8_t flash_request_flag;
extern flash_store_t flash_write_data;

void flashDataInit(void);
void flashDataSave(void);
void getGrindDataFromFlash();

uint32_t FLASH_ReadWord(uint32_t Address);
HAL_StatusTypeDef FLASH_EraseSector(uint32_t Sector);
HAL_StatusTypeDef FLASH_WriteWord(uint32_t Address, uint32_t Data);
HAL_StatusTypeDef FLASH_WriteData(uint32_t Address, uint32_t *pData, uint32_t Size);
// void flash_store_read(flash_store_t *store) ;
// void flash_store_write(flash_store_t *store);

#endif /* __FLASH_IO_H */
