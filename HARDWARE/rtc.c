#include "rtc.h"

I2C_HandleTypeDef hi2c3;

void I2C3_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // 1. 使能时钟
    __HAL_RCC_I2C3_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // 2. 配置GPIO引脚
    // PA8 (I2C3_SCL) - 复用功能AF4
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;        // 开漏输出
    GPIO_InitStruct.Pull = GPIO_PULLUP;           // 上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // PC9 (I2C3_SDA) - 复用功能AF4
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    // 3. 配置I2C参数
    hi2c3.Instance = I2C3;
    hi2c3.Init.ClockSpeed = 100000;               // 100kHz标准模式
    hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;       // 占空比
    hi2c3.Init.OwnAddress1 = 0;                   // 主模式地址设为0
    hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    
    // 4. 初始化I2C
    if (HAL_I2C_Init(&hi2c3) != HAL_OK)
    {
        // errors
    }
}

// 如果需要，添加MspInit回调
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
    if(hi2c->Instance == I2C3)
    {
        // GPIO和时钟初始化可以放在这里
    }
}

// 私有函数声明
static uint8_t BCD_to_DEC(uint8_t bcd);
static uint8_t DEC_to_BCD(uint8_t dec);
static HAL_StatusTypeDef ISL1208_WriteEnable(void);
static HAL_StatusTypeDef ISL1208_WriteDisable(void);

/**
 * @brief  初始化ISL1208 RTC
 * @retval HAL状态
 */
HAL_StatusTypeDef ISL1208_Init(void)
{
    uint8_t data[2];
    HAL_StatusTypeDef status;

    I2C3_Init();
    printf("ISL1208 RTC init\n");
    // 1. 检查芯片是否存在
    status = HAL_I2C_IsDeviceReady(&hi2c3, ISL1208_I2C_ADDR << 1, 3, 100);
    if (status != HAL_OK) {
        return status;
    }
    printf("ISL1208 RTC found\n");
    
    // 2. 读取状态寄存器
    data[0] = ISL1208_REG_SR;
    status = HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, data, 1, 100);
    if (status == HAL_OK) {
        HAL_I2C_Master_Receive(&hi2c3, ISL1208_I2C_ADDR << 1, &data[1], 1, 100);
    }

    if ( data[1] & ISL1208_SR_RTCF){
        ///clear rtc fault
        data[1] = (data[1] & ~ISL1208_SR_RTCF);
        uint8_t write_sr_data[2] = {ISL1208_REG_SR, data[1]};
        HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, write_sr_data, 2, 100);
    }

    
    // 3. 配置为24小时制
    data[0] = ISL1208_REG_HR;
    status = HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, data, 1, 100);
    if (status == HAL_OK) {
        HAL_I2C_Master_Receive(&hi2c3, ISL1208_I2C_ADDR << 1, &data[1], 1, 100);
        
        // 设置为24小时制
        data[1] |= ISL1208_HR_MIL;
        
        // 使能写操作
        ISL1208_WriteEnable();
        
        // 写回寄存器
        uint8_t write_data[2] = {ISL1208_REG_HR, data[1]};
        HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, write_data, 2, 100);
        
        // 禁用写操作
        ISL1208_WriteDisable();
    }
    
    return status;
}

/**
 * @brief  设置RTC时间
 * @param  time: 时间结构体指针
 * @retval HAL状态
 */
HAL_StatusTypeDef ISL1208_SetTime(ISL1208_Time_t *time)
{
    uint8_t data[8];
    HAL_StatusTypeDef status;
    
    // 使能写操作
    status = ISL1208_WriteEnable();
    if (status != HAL_OK) return status;
    
    // 准备数据: 寄存器地址 + 时间数据
    data[0] = ISL1208_REG_SC;  // 起始寄存器地址
    
    // 转换并填充时间数据
    data[1] = DEC_to_BCD(time->seconds) & ISL1208_SECONDS_MASK;
    data[2] = DEC_to_BCD(time->minutes) & ISL1208_MINUTES_MASK;
    
    // 小时处理
    if (time->format_12h) {
        // 12小时制
        uint8_t hour_bcd = DEC_to_BCD(time->hours % 12);
        if (time->hours >= 12) {
            hour_bcd |= ISL1208_HR_PM;  // 设置PM位
        }
        data[3] = hour_bcd & ISL1208_HOUR_12_MASK;
    } else {
        // 24小时制
        data[3] = (DEC_to_BCD(time->hours) & ISL1208_HOUR_24_MASK) | ISL1208_HR_MIL;
    }
    
    data[4] = DEC_to_BCD(time->date) & ISL1208_DATE_MASK;
    data[5] = DEC_to_BCD(time->month) & ISL1208_MONTH_MASK;
    data[6] = DEC_to_BCD(time->year);
    data[7] = DEC_to_BCD(time->day) & ISL1208_DAY_MASK;
    
    // 写入时间数据
    status = HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, data, 8, 100);
    
    // 禁用写操作
    ISL1208_WriteDisable();
        
    
    return status;
}

int ISL1208_test(void)
{
    uint8_t data[7] = {0};
    uint8_t reg_addr = ISL1208_REG_SC;
    HAL_StatusTypeDef status;
    


    // uint8_t write_data2[2] = {ISL1208_REG_SR, 0x90};
    // HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, write_data2, 2, 100);

    // 发送寄存器起始地址
    status = HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, &reg_addr, 1, 100);
    if (status != HAL_OK) return status;
    
    // 读取7个时间寄存器
    status = HAL_I2C_Master_Receive(&hi2c3, ISL1208_I2C_ADDR << 1, data, 7, 100);
    if (status != HAL_OK) return status;

    for(int i = 0; i < 7; i++) {
        printf("data[%d] = %d\n",i, data[i]);
    }
}
#if 1
/**
 * @brief  读取RTC时间
 * @param  time: 时间结构体指针
 * @retval HAL状态
 */
HAL_StatusTypeDef ISL1208_GetTime(ISL1208_Time_t *time)
{
    uint8_t data[7];
    uint8_t reg_addr = ISL1208_REG_SC;
    HAL_StatusTypeDef status;
    
    // 发送寄存器起始地址
    status = HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, &reg_addr, 1, 100);
    if (status != HAL_OK) return status;
    
    // 读取7个时间寄存器
    status = HAL_I2C_Master_Receive(&hi2c3, ISL1208_I2C_ADDR << 1, data, 7, 100);
    if (status != HAL_OK) return status;
    
    // 解析数据
    time->seconds = BCD_to_DEC(data[0] & ISL1208_SECONDS_MASK);
    time->minutes = BCD_to_DEC(data[1] & ISL1208_MINUTES_MASK);
    printf("ISL1208 RTC seconds = %d\n",time->seconds);
    // 检查是否为24小时制
    if (data[2] & ISL1208_HR_MIL) {
        // 24小时制
        time->format_12h = 0;
        time->hours = BCD_to_DEC(data[2] & ISL1208_HOUR_24_MASK);
    } else {
        // 12小时制
        time->format_12h = 1;
        uint8_t hour = BCD_to_DEC(data[2] & ISL1208_HOUR_12_MASK);
        if (data[2] & ISL1208_HR_PM) {
            time->hours = hour + 12;  // PM
            if (time->hours == 24) time->hours = 12;
        } else {
            time->hours = hour;       // AM
            if (time->hours == 12) time->hours = 0;
        }
    }
    
    time->date = BCD_to_DEC(data[3] & ISL1208_DATE_MASK);
    time->month = BCD_to_DEC(data[4] & ISL1208_MONTH_MASK);
    time->year = BCD_to_DEC(data[5]);
    time->day = BCD_to_DEC(data[6] & ISL1208_DAY_MASK);
    
    return HAL_OK;
}
#endif
/**
 * @brief  使能写操作
 */
static HAL_StatusTypeDef ISL1208_WriteEnable(void)
{
    uint8_t data[2];
    HAL_StatusTypeDef status;
    
    // 读取状态寄存器
    data[0] = ISL1208_REG_SR;
    status = HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, data, 1, 100);
    if (status != HAL_OK) return status;
    
    HAL_I2C_Master_Receive(&hi2c3, ISL1208_I2C_ADDR << 1, &data[1], 1, 100);
    
    // 设置WRTC位
    data[1] |= ISL1208_SR_WRTC;
    uint8_t write_data2[2] = {ISL1208_REG_SR, data[1]};
    return HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, write_data2, 2, 100);
}

/**
 * @brief  禁用写操作
 */
static HAL_StatusTypeDef ISL1208_WriteDisable(void)
{
    uint8_t data[2];
    
    // 读取状态寄存器
    data[0] = ISL1208_REG_SR;
    HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, data, 1, 100);
    HAL_I2C_Master_Receive(&hi2c3, ISL1208_I2C_ADDR << 1, &data[1], 1, 100);
    
    // 清除RWEL和WRTC位
    data[1] &= ~(ISL1208_SR_WRTC);
    uint8_t write_data[2] = {ISL1208_REG_SR, data[1]};
    
    return HAL_I2C_Master_Transmit(&hi2c3, ISL1208_I2C_ADDR << 1, write_data, 2, 100);
}

/**
 * @brief  BCD转十进制
 */
static uint8_t BCD_to_DEC(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

/**
 * @brief  十进制转BCD
 */
static uint8_t DEC_to_BCD(uint8_t dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}
