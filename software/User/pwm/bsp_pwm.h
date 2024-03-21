/*引脚配置
	L_EN 接PA1
	R_EN 接PA2
*/
#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include "stm32f10x.h"

/*右轮为通道3，左轮通道4*/
 
void PWM_GPIO_Config(void);
void PWM_TIM_Config(uint16_t,uint16_t);
void PWM_Channel_Config(void);														//右轮的速度调节初始化
	 	
#endif /* __BSP_PWM_H */
