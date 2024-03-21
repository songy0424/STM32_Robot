#ifndef __BSP_ADC_H
#define	__BSP_ADC_H

#include "stm32f10x.h"

#define    ADC_x                         ADC1
#define    ADC_CHANNEL                   ADC_Channel_1
#define 	 ADC_DMA_CLK									 RCC_AHBPeriph_DMA1
#define    ADC_DMA_CHANNEL               DMA1_Channel1

void ADC1_Init(void);
float Read_ADC_data(void);

#endif /* __BSP_ADC_H */
