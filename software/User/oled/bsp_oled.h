/*“˝Ω≈≈‰÷√
	SCL Ω”PB10
	SDA Ω”PB11
*/

#ifndef __BSP_OLED_H
#define __BSP_OLED_H

#include "stm32f10x.h"

#define  OLED_SCL_PORT 										GPIOB
#define  OLED_SCL_PIN  						 				GPIO_Pin_10

#define  OLED_SDA_PORT 										GPIOB
#define  OLED_SDA_PIN  						 				GPIO_Pin_11

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

#endif /*__BSP_OLED_H */
