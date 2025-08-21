#include "modbus.h"

UART_HandleTypeDef huart2;

// ================== 初始化 ==================
void Modbus_Init(uint32_t baudrate)
{
    // 1. 打开时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();

    // 2. 配置 GPIO
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // PA0 - TX
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA1 - RX
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA2 - DE
    GPIO_InitStruct.Pin = MODBUS_DE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(MODBUS_DE_GPIO, &GPIO_InitStruct);

    HAL_GPIO_WritePin(MODBUS_DE_GPIO, MODBUS_DE_PIN, GPIO_PIN_RESET); // 默认接收

    // 3. 配置 UART
    huart2.Instance = USART2;
    huart2.Init.BaudRate = baudrate;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        // 错误处理（可以加 while(1) 或 debug 打印）
    }
}

// ================== 发送函数 ==================
void Modbus_Send(uint8_t *pData, uint16_t Size)
{
    // 切换到发送模式
    HAL_GPIO_WritePin(MODBUS_DE_GPIO, MODBUS_DE_PIN, GPIO_PIN_SET);

    HAL_UART_Transmit(&huart2, pData, Size, HAL_MAX_DELAY);

    // 切回接收模式
    HAL_GPIO_WritePin(MODBUS_DE_GPIO, MODBUS_DE_PIN, GPIO_PIN_RESET);
}

// ================== CRC16 ==================
uint16_t Modbus_CRC16(uint8_t *buf, uint16_t len)
{
    uint16_t crc = 0xFFFF;
    for (int pos = 0; pos < len; pos++) {
        crc ^= (uint16_t)buf[pos];
        for (int i = 0; i < 8; i++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void Modbus_SendGrindTime(uint8_t cup_size)
{
    uint8_t frame[8];
    uint16_t grind_time;

    // 选择磨豆时间
    if (cup_size == 0) {
        grind_time = 10;   // 小杯
    } else {
        grind_time = 20;   // 大杯
    }

    // 构造 Modbus 帧
    frame[0] = 0x01;       // 从机地址
    frame[1] = 0x06;       // 功能码：写单寄存器
    frame[2] = 0x00;       
    frame[3] = 0x01;       // 寄存器地址 0x0001
    frame[4] = (grind_time >> 8) & 0xFF;  // 高字节
    frame[5] = grind_time & 0xFF;         // 低字节

    uint16_t crc = Modbus_CRC16(frame, 6);
    frame[6] = crc & 0xFF;         // CRC低字节
    frame[7] = (crc >> 8) & 0xFF;  // CRC高字节

    // 发送
    Modbus_Send(frame, 8);
}