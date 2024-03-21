#ifndef __INIT_H
#define __INIT_H

#include "stm32f10x.h"			

void GPIO_INIT(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pinx, GPIOMode_TypeDef GPIO_Modex);   	//只能初始化GPIO
void INIT_ALL(void);  				//所以初始化都放在里面

#endif /* __INIT_H */
