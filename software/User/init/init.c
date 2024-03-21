/*
 * @Date: 2023-09-21 16:14:37
 * @LastEditTime: 2023-09-21 17:26:54
 * @Description:
 */
#include "init.h"
#include "bsp_pwm.h"
#include "bsp_motor.h"
#include "bsp_usart.h"
#include "bsp_oled.h"
#include "bsp_encoder.h"
#include "mpu6050.h"
#include "timer.h"
#include "delay.h"
#include "bsp_adc.h"

void GPIO_INIT(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pinx, GPIOMode_TypeDef GPIO_Modex)
{
	GPIO_InitTypeDef GPIO_InitStructure; // 定义GPIO_InitTypeDef结构体

	if (GPIOx == GPIOA)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启引脚时钟
	else if (GPIOx == GPIOB)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启引脚时钟
	else if (GPIOx == GPIOC)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 开启引脚时钟
	else if (GPIOx == GPIOD)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // 开启引脚时钟
	else if (GPIOx == GPIOE)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); // 开启引脚时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Modex;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void INIT_ALL(void)
{
	Motor_GPIO_Config();		 	// 电机的GPIO初始化
	PWM_GPIO_Config();		 		// PWM的GPIO初始化
	PWM_TIM_Config(1000, 3); 	// PWM的定时器初始化
	PWM_Channel_Config();	 		// PWM的通道初始化
	OLED_Init();			 				// OLED初始化
	USART1_Init();			 			// 串口1初始化
	Encoder_Init();			 			// 编码器初始化
	delay_init();			 				// 延迟函数初始化
	//	ADC1_Init();
	MPU_Init();
	delay_ms(700);
	if (mpu_dmp_init() == 0)
	{
	}
	Timer1_Init(10); 					// 将TIM1配置为10ms定时中断，周期性运行控制算法
}
