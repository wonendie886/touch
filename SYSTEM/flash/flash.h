#ifndef FLASH_H
#define FLASH_H

#include "stm32f4xx_hal.h"  // 确保已包含HAL库头文件

/* 根据你的芯片型号定义Flash大小和起始地址 */
#define STM32_FLASH_BASE        0x08000000UL    /* STM32 Flash的起始地址 */
#define STM32_FLASH_SIZE        (512 * 1024)    /* STM32F407VET6 的Flash大小为512KB */
#define FLASH_END_ADDRESS       (STM32_FLASH_BASE + STM32_FLASH_SIZE)


#define USER_FLASH_START_ADDR   0x080E0000      /* Sector 11 起始地址 */
#define USER_FLASH_SECTOR       FLASH_SECTOR_11  /* 对应扇区编号 */
#define MAX_TEXT_LEN  5
typedef struct {
    char label1_text[MAX_TEXT_LEN];
    char label2_text[MAX_TEXT_LEN];
    char label3_text[MAX_TEXT_LEN];
    char label4_text[MAX_TEXT_LEN];
    char label5_text[MAX_TEXT_LEN];
    char label6_text[MAX_TEXT_LEN];

} flash_store_t;

extern volatile uint8_t flash_request_flag;
extern flash_store_t flash_write_data;
/* 函数声明 */
HAL_StatusTypeDef FLASH_Init(void);
uint32_t FLASH_ReadWord(uint32_t Address);
HAL_StatusTypeDef FLASH_EraseSector(uint32_t Sector);
HAL_StatusTypeDef FLASH_WriteWord(uint32_t Address, uint32_t Data);
HAL_StatusTypeDef FLASH_WriteData(uint32_t Address, uint32_t *pData, uint32_t Size);
void flash_store_read(flash_store_t *store) ;
void flash_store_write(flash_store_t *store);

#endif /* __FLASH_IO_H */
