#ifndef FLASH_H
#define FLASH_H

#include "stm32f4xx_hal.h"  // 确保已包含HAL库头文件

/* 根据你的芯片型号定义Flash大小和起始地址 */
#define STM32_FLASH_BASE        0x08000000UL    /* STM32 Flash的起始地址 */
#define STM32_FLASH_SIZE        (512 * 1024)    /* STM32F407VET6 的Flash大小为512KB */
#define FLASH_END_ADDRESS       (STM32_FLASH_BASE + STM32_FLASH_SIZE)

/* 
 * !!! 重要：选择安全的操作地址 !!!
 * 务必根据你的程序实际大小，选择一个绝对不会被程序代码使用的扇区。
 * 例如，如果你的程序很小，可以使用靠后的扇区，如 Sector 6 或 Sector 7。
 * 在操作前，务必检查编译生成的 .map 文件，确保你的程序代码不会覆盖到你打算使用的地址。
 * 这里以 Sector 6 的起始地址为例，请根据实际情况修改！
 */
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
