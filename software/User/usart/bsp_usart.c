#include "bsp_usart.h"
#include "init.h"
#include <string.h>

u8 Fore,Back,Left,Right;

void USART1_Init(void)
{
	USART_InitTypeDef USART_InitStructure;   																					//串口参数配置结构体变量
	
	//串口中断配置结构体变量
	GPIO_INIT(GPIOA,GPIO_Pin_9,GPIO_Mode_AF_PP);
	GPIO_INIT(GPIOA,GPIO_Pin_10,GPIO_Mode_IN_FLOATING);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		                          								

	//USART 初始化设置
	USART_InitStructure.USART_BaudRate 						= 115200;                 					//串口波特率为115200
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b;  						//字长为8位数据格式
	USART_InitStructure.USART_StopBits 						= USART_StopBits_1;        					//一个停止位
	USART_InitStructure.USART_Parity 							= USART_Parity_No;           				//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  	//无硬件数据流控制
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;	  //收发模式
	USART_Init(USART1, &USART_InitStructure);                     										//初始化串口1

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 																		//使能中断
	USART_Cmd(USART1, ENABLE);                     																		//使能串口1
	USART_ClearFlag(USART1, USART_FLAG_TC);        																		//清串口1发送标志
}
