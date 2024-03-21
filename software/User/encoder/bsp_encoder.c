/*
 * @Date: 2023-09-21 16:14:37
 * @LastEditTime: 2023-09-21 17:07:44
 * @Description:
 */
#include "bsp_encoder.h"
#include "init.h"

void Encoder_Init(void) // 编码器
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct; // 定义结构体
	TIM_ICInitTypeDef TIM_ICInitStruct;				// 定义结构体

	GPIO_INIT(GPIOA, GPIO_Pin_6, GPIO_Mode_IN_FLOATING); // GPIO初始化
	GPIO_INIT(GPIOA, GPIO_Pin_7, GPIO_Mode_IN_FLOATING); // GPIO初始化
	GPIO_INIT(GPIOB, GPIO_Pin_6, GPIO_Mode_IN_FLOATING); // GPIO初始化
	GPIO_INIT(GPIOB, GPIO_Pin_7, GPIO_Mode_IN_FLOATING); // GPIO初始化

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 时钟初始化
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // 时钟初始化

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct); // 初始化定时器
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 配置编码器模式
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 配置编码器模式

	TIM_ICStructInit(&TIM_ICInitStruct); // 初始化输入捕获
	TIM_ICInitStruct.TIM_ICFilter = 10;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_ICInit(TIM4, &TIM_ICInitStruct);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 配置溢出更新中断标志位
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_SetCounter(TIM3, 0); // 清零定时器计数值
	TIM_SetCounter(TIM4, 0);

	TIM_Cmd(TIM3, ENABLE); // 开启定时器
	TIM_Cmd(TIM4, ENABLE);
}

/**********************
编码器
速度读取函数
入口参数：定时器
**********************/

int Read_Encoder_TIM3(void)
{
	int Encoder_Value;
	Encoder_Value = TIM_GetCounter(TIM3); // 读取计数
	if (Encoder_Value > 0xefff)
		Encoder_Value = Encoder_Value - 0xffff; // 转化计数值为有方向的值，大于0正转，小于0反转。
												// TIM3->CNT范围为0-0xffff，初值为0。
	TIM_SetCounter(TIM3, 0);					// 读取完后计数清零

	return Encoder_Value; // 返回值
}

int Read_Encoder_TIM4(void)
{
	int Encoder_Value;
	Encoder_Value = TIM_GetCounter(TIM4); // 读取计数
	if (Encoder_Value > 0xefff)
		Encoder_Value = Encoder_Value - 0xffff; // 转化计数值为有方向的值，大于0正转，小于0反转。
												// TIM4->CNT范围为0-0xffff，初值为0。
	TIM_SetCounter(TIM4, 0);					// 读取完后计数清零

	return Encoder_Value; // 返回值
}

 void TIM3_IRQHandler(void)
 {
 	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=0)
 	{
 		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
 	}
 }
 void TIM4_IRQHandler(void)
 {
 	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=0)
 	{
 		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
 	}
 }
