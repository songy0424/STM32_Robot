/*引脚配置
	驱动 	接PA6		  TIM3Ch1
				接PA7		  TIM3Ch2
	
	角度 	接PB6			TIM4Ch1
				接PB7			TIM4Ch2
*/

#ifndef  __BSP_ENCODER_H
#define  __BSP_ENCODER_H
#include "stm32f10x.h"

int Read_Encoder_TIM3(void);
int Read_Encoder_TIM4(void);
void Encoder_Init(void);

#endif /*__BSP_ENCODER_H*/

