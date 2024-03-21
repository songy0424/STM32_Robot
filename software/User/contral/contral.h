#ifndef __CONTRAL_H
#define __CONTRAL_H

#include "stm32f10x.h"

#define ABS(x) ((x)>=0?(x):-(x))

void Core_App_X(void);																//驱动轮控制
void Core_App_Y(void);				  											//动量轮控制

void Motor_SetAngle(int pwm);													//驱动轮速度
void Motor_SetSpeed(int pwm);   											//动量轮速度
void Limit(int *pwm);
void Limit1(int *pwm);
void Stop(void);

int Vertical(float Med,float Angle,float gyro_x);			//动量直立环
int Velocity (int encoder_motor);											//动量速度环

int Vertical1(float Med,float Angle,float gyro_x);		//驱动直立环
int Velocity1 (int encoder_motor);										//驱动速度环

#endif /* __CONTRAL_H */
