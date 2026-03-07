#include "adc.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

uint32_t adc_buffer[ADC_BUFFER_SIZE];
uint32_t adc_average_value = 0;

/* GPIO配置 */
void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* 使能GPIO时钟 */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* 配置PA7为模拟模式（ADC功能） */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* DMA配置 */
void MX_DMA_Init(void)
{
    /* 使能DMA2时钟 */
    __HAL_RCC_DMA2_CLK_ENABLE();

    /* 配置DMA2_Stream0用于ADC1 */
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;  // ADC1使用通道0
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;  // 循环模式
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_adc1);

    /* 连接DMA到ADC */
    __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
}

/* ADC配置 */
void MX_ADC1_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    MX_GPIO_Init();
    /* 使能ADC时钟 */
    __HAL_RCC_ADC1_CLK_ENABLE();

    /* ADC基本配置 */
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;  // 21MHz ADC时钟
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;            // 12位分辨率
    hadc1.Init.ScanConvMode = DISABLE;                     // 单通道模式
    hadc1.Init.ContinuousConvMode = ENABLE;                // 连续转换
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;                         // 1个转换通道
    hadc1.Init.DMAContinuousRequests = ENABLE;              // DMA连续请求
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    HAL_ADC_Init(&hadc1);

    /* 配置ADC通道7 (PA7) */
    sConfig.Channel = ADC_CHANNEL_7;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;  // 采样时间
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, ADC_BUFFER_SIZE);
}

/* 计算ADC平均值 */
uint32_t Calculate_ADC_Average(uint32_t *buffer, uint32_t size)
{
    uint32_t sum = 0;
    uint32_t i;
    
    for(i = 0; i < size; i++)
    {
        sum += buffer[i];
    }
    
    return sum / size;
}

/* 获取ADC值并转换为电压 */
float Get_ADC_Voltage(void)
{
    uint32_t adc_value;
    float voltage;
    
    /* 获取最新的ADC平均值 */
    adc_average_value = Calculate_ADC_Average(adc_buffer, ADC_BUFFER_SIZE);
    adc_value = adc_average_value;
    
    /* 转换为电压 (参考电压3.3V, 12位ADC: 4096) */
    voltage = (float)adc_value * 3.3f / 4096.0f;

    printf("Avg adc_value: %d, Voltage: %.2f V\r\n", 0, voltage);
    return voltage;
}

