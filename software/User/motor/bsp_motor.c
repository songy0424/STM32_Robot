#include "bsp_motor.h"
#include "bsp_pwm.h"
#include "init.h" 

void Motor_GPIO_Config(void)  							//≥ı ºªØGPIO
{ 
	//GPIO_WriteBit(GPIOB,IN1_Pin|IN2_Pin|START_Pin|DIR_Pin, Bit_RESET);
	GPIO_INIT(GPIOB,IN1_Pin, GPIO_Mode_Out_PP);
	GPIO_INIT(GPIOB,IN2_Pin, GPIO_Mode_Out_PP);
	GPIO_INIT(GPIOB,START_Pin, GPIO_Mode_Out_PP);
	GPIO_INIT(GPIOB,DIR_Pin, GPIO_Mode_Out_PP);
}
