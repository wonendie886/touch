#include "flash.h"

uint32_t pending_grind_time = 0;
GrindConfig_t pending_config;
uint32_t *flash_dest = NULL;
uint32_t *flash_src = NULL;
uint32_t flash_words_remaining = 0;

// 启用CRC时钟并初始化
static void crc_init(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;  // 使能CRC时钟
  CRC->CR = CRC_CR_RESET;             // 复位CRC计算器
}

// 硬件CRC32计算（4字节对齐版本）
static uint32_t crc_calculate(uint32_t *data, uint32_t count) {
  CRC->CR |= CRC_CR_RESET;  // 开始新计算前复位

  while (count--) {
    CRC->DR = *data++;
  }
  return CRC->DR;  // 返回最终校验值
}
// flash.c
#include "flash.h"
#include "stm32f4xx.h"



// 存储配置到Flash
void FLASH_StoreConfig(uint32_t grind_time) {
  // 初始化配置结构体
  GrindConfig_t config = {
    .grind_time_s = grind_time,
    .checksum = 0  // 先临时置0
  };

  // 计算有效数据CRC（不包含checksum自身）
  crc_init();
  config.checksum = crc_calculate(&config.grind_time_s, 
                                 sizeof(config.grind_time_s)/sizeof(uint32_t));

  // 打印要存储的数据
  printf("准备存储数据: grind_time=%d, checksum=0x%08X\n", config.grind_time_s, config.checksum);

  // 准备Flash操作
  FLASH->KEYR = 0x45670123;  // 解锁序列1
  FLASH->KEYR = 0xCDEF89AB;  // 解锁序列2

  // 擦除扇区（11号扇区）
  FLASH->CR |= FLASH_CR_SER;       // 扇区擦除使能
  FLASH->CR |= (FLASH_SECTOR << FLASH_CR_SNB_Pos);  // 选择扇区
  FLASH->CR |= FLASH_CR_STRT;      // 开始擦除
  while (FLASH->SR & FLASH_SR_BSY) // 等待完成
    ;

  printf("扇区擦除完成\n");

  // 按字（32bit）写入
  uint32_t *dest = (uint32_t*)GRIND_TIME_ADDR;
  uint32_t *src = (uint32_t*)&config;
  for (int i = 0; i < sizeof(config)/4; i++) {
    FLASH->CR |= FLASH_CR_PG;  // 编程使能
    *dest = *src++;

    printf("写入地址 0x%08X: 0x%08X\n", (uint32_t)dest, *src);

    while (!(FLASH->SR & FLASH_SR_EOP)) // 等待完成
      ;
    FLASH->SR = FLASH_SR_EOP;  // 清除标志
    dest++;
  }

  // 锁定Flash
  FLASH->CR |= FLASH_CR_LOCK;

  printf("Flash存储完成并已锁定\n");

}

// 从Flash加载配置
int FLASH_LoadConfig(uint32_t *saved_time) {
  GrindConfig_t *config = (GrindConfig_t*)GRIND_TIME_ADDR;

    // 打印Flash中的数据
    printf("从Flash地址 0x%08X 读取数据:\n", (uint32_t)GRIND_TIME_ADDR);
    printf("grind_time_s: 0x%08X (%u)\n", config->grind_time_s, config->grind_time_s);
    printf("checksum: 0x%08X\n", config->checksum);

  // 检查是否初始状态（全FF）
  if (config->grind_time_s == 0xFFFFFFFF){ 

    printf("Flash中无有效数据全FF\n");

    return 0; // 无有效数据
  }
  // 验证CRC
  crc_init();
  uint32_t calc_crc = crc_calculate(&config->grind_time_s, 
                                   sizeof(config->grind_time_s)/4);
  
  printf("计算得到的CRC: 0x%08X, 存储的CRC: 0x%08X\n", calc_crc, config->checksum);

  if (calc_crc != config->checksum){
    printf("Flash中数据校验失败\n");
    return -1; // 校验失败
  }
  *saved_time = config->grind_time_s;
  printf("数据校验成功，磨豆时间: %u秒\n", *saved_time);
  return 1;
}