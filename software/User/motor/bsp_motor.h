/*引脚配置
	驱动：
	IN1 接PB12
	IN2 接PB13

	角度：
	START 接PB14
	DIR 	接PB15

*/

#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H

#include "stm32f10x.h"

#define High    						1
#define Low     						0

#define IN1_GPIO_Port 				GPIOB
#define IN1_Pin 							GPIO_Pin_12

#define IN2_GPIO_Port 				GPIOB
#define IN2_Pin 							GPIO_Pin_13

#define START_GPIO_Port 			GPIOB
#define START_Pin 						GPIO_Pin_14

#define DIR_GPIO_Port 				GPIOB
#define DIR_Pin 							GPIO_Pin_15

#define IN1(a)							a?GPIO_SetBits(IN1_GPIO_Port, IN1_Pin)\
																		:GPIO_ResetBits(IN1_GPIO_Port, IN1_Pin)
																
#define IN2(a)							a?GPIO_SetBits(IN2_GPIO_Port, IN2_Pin)\
																		:GPIO_ResetBits(IN2_GPIO_Port, IN2_Pin)  																		
		
#define START(a)  					a?GPIO_SetBits(START_GPIO_Port, START_Pin)\
																		:GPIO_ResetBits(START_GPIO_Port, START_Pin)

#define DIR(a)           		a?GPIO_SetBits(DIR_GPIO_Port, DIR_Pin)\
																		:GPIO_ResetBits(DIR_GPIO_Port, DIR_Pin)

void Motor_GPIO_Config(void);  							//定义初始化函数

#endif /* __BSP_MOTOR_H */
