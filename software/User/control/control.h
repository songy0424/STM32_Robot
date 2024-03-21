/*
 * @Date: 2023-07-14 13:48:43
 * @LastEditTime: 2023-07-17 17:00:57
 * @Description: 包括全部的电机控制宏定义及声明
 */
#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"

extern u8 Line_flag;

#define High 1
#define Low 0

/*限制最大速度*/
#define PWM_MAX_PERIOD_COUNT (1000 - 30)
#define PWM2_MAX_PERIOD_COUNT (1000 - 30)

/*编码器物理分辨率*/
#define ENCODER_RESOLUTION 11

/*经过倍频后的总分辨率*/
#define ENCODER_TOTAL_RESOLUTION (ENCODER_RESOLUTION * 4)

/*减速电机减速比*/
#define REDUCTION_RATIO 30

#define SPEED_PID_PERIOD 20	 // 定时器7中断周期
#define TARGET_SPEED_MAX 120 // 最大速度限制

#define LUN_JU 17.5 // 单位cm
#define HeadToWheelCM 13

#define L_IN1(a) a ? GPIO_SetBits(GPIOB, GPIO_Pin_6) \
				   : GPIO_ResetBits(GPIOB, GPIO_Pin_6)

#define L_IN2(a) a ? GPIO_SetBits(GPIOB, GPIO_Pin_7) \
				   : GPIO_ResetBits(GPIOB, GPIO_Pin_7)

#define R_IN1(a) a ? GPIO_SetBits(GPIOB, GPIO_Pin_8) \
				   : GPIO_ResetBits(GPIOB, GPIO_Pin_8)

#define R_IN2(a) a ? GPIO_SetBits(GPIOB, GPIO_Pin_9) \
				   : GPIO_ResetBits(GPIOB, GPIO_Pin_9)

/*设置速度*/
#define SET_COMPAER(ChannelPulse) TIM_SetCompare3(TIM2, ChannelPulse)
#define SET2_COMPAER(ChannelPulse) TIM_SetCompare4(TIM2, ChannelPulse)

/*使能输出*/
#define MOTOR_ENABLE() TIM_Cmd(TIM2, ENABLE)

/*禁用输出*/
#define MOTOR_DISABLE() TIM_Cmd(TIM2, DISABLE)

typedef enum
{
	left_90,
	right_90,
	back_180
} spin_dir_t;

typedef enum
{
	MOTOR_FWD = 0, // 前进
	MOTOR_REV,	   // 后退
} motor_dir_t;

float speed_pid_control(void);
float location_pid_control(void);
float speed2_pid_control(void);
float location2_pid_control(void);
void Location_Speed_control(void);

void Car_go(int32_t location_cm);
void spin_Turn(spin_dir_t zhuanxiang);

void MotorOutput(int nMotorPwm, int nMotor2Pwm);
void set_motor_speed(uint16_t v, uint16_t v2);
void set_motor_direction(motor_dir_t dir);
void set_motor2_direction(motor_dir_t dir);
void set_motor_enable(void);
void set_motor_disable(void);

#endif /* CONTROL */
