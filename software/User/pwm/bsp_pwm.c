/*
 * @Date: 2023-09-21 16:14:37
 * @LastEditTime: 2023-09-21 17:08:10
 * @Description:
 */
#include "bsp_pwm.h"
#include "init.h"
#include "bsp_motor.h"

void PWM_GPIO_Config(void) // PWM的GPIO初始化
{
	START(0);
	GPIO_INIT(GPIOA, GPIO_Pin_3, GPIO_Mode_AF_PP);
	GPIO_INIT(GPIOA, GPIO_Pin_2, GPIO_Mode_AF_PP);
}

void PWM_TIM_Config(uint16_t arr, uint16_t psc) // 初始化PWM
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitStruct.TIM_Period = arr - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc - 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
}

void PWM_Channel_Config(void) // 通道初始化
{
	TIM_OCInitTypeDef TIM_OCInitStruct;

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;			   // 选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;	   // 输出极性:TIM输出比较极性高

	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); // 使能TIM2在CCR3上的预装载寄存器

	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); // 使能TIM2在CCR4上的预装载寄存器

	TIM_Cmd(TIM2, ENABLE);
}
