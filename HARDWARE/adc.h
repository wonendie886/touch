#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define ADC_BUFFER_SIZE   100  // DMA缓冲区大小

void MX_DMA_Init(void);
void MX_ADC1_Init(void);
float Get_ADC_Voltage(void);

#endif 
