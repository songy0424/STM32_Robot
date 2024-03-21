/*
 * @Date: 2023-07-14 13:48:43
 * @LastEditTime: 2023-07-17 17:08:14
 * @Description:PID初始化
 */
#include "data_pid.h"

_pid pid_speed, pid_speed2;
_pid pid_location, pid_location2;

void PID_param_init(void) // 位置式PID参数
{
	/* 位置相关初始化参数 */
	pid_location.target_val = 0.0;
	pid_location.actual_val = 0.0;
	pid_location.err = 0.0;
	pid_location.err_last = 0.0;
	pid_location.integral = 0.0;

	pid_location.Kp = 0.225;
	pid_location.Ki = 0.0;
	pid_location.Kd = 0.0;

	/* 速度相关初始化参数 */
	pid_speed.target_val = 0.0;
	pid_speed.actual_val = 0.0;
	pid_speed.err = 0.0;
	pid_speed.err_last = 0.0;
	pid_speed.integral = 0.0;

	pid_speed.Kp = 2.6;
	pid_speed.Ki = 0.787;
	pid_speed.Kd = 0.25;

	/* 位置相关初始化参数 */
	pid_location2.target_val = 0.0;
	pid_location2.actual_val = 0.0;
	pid_location2.err = 0.0;
	pid_location2.err_last = 0.0;
	pid_location2.integral = 0.0;

	pid_location2.Kp = 0.225;
	pid_location2.Ki = 0.0;
	pid_location2.Kd = 0.0;

	/* 速度相关初始化参数 */
	pid_speed2.target_val = 0.0;
	pid_speed2.actual_val = 0.0;
	pid_speed2.err = 0.0;
	pid_speed2.err_last = 0.0;
	pid_speed2.integral = 0.0;

	pid_speed2.Kp = 2.6;
	pid_speed2.Ki = 0.787;
	pid_speed2.Kd = 0.25;
}

/**
 * @brief 设置目标值
 * @param {_pid} *pid
 * @param {float} temp_val 目标值
 * @return
 */
void set_pid_target(_pid *pid, float temp_val)
{
	pid->target_val = temp_val; // ?è???±?°????±ê??
}

/**
 * @brief 获取目标值
 * @param {_pid} *pid
 * @return 目标值
 */
float get_pid_target(_pid *pid)
{
	return pid->target_val; // ?è???±?°????±ê??
}
/**
 * @brief 设置系数
 * @param {_pid} *pid
 * @param {float} p
 * @param {float} i
 * @param {float} d
 * @return {*}
 */
void set_p_i_d(_pid *pid, float p, float i, float d)
{
	pid->Kp = p;
	pid->Ki = i;
	pid->Kd = d;
}

/**
 * @brief 位置PID算法实现
 * @param {_pid} *pid
 * @param {float} actual_val 实际值
 * @return 输出PID计算后的值
 */
float location_pid_realize(_pid *pid, float actual_val) // ?????·????Kp??????????
{
	/*计算偏差*/
	pid->err = pid->target_val - actual_val;

	//    /* 设定闭环死区 */   //外环死区可以不要
	//    if((pid->err >= -0.1) && (pid->err <= 0.1))
	//    {
	//      pid->err = 0;
	//      pid->integral = 0;
	//    }

	/*误差累积*/
	pid->integral += pid->err;

	/*PID算法实现*/
	pid->actual_val = pid->Kp * pid->err + pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);

	/*误差传递*/
	pid->err_last = pid->err;

	/*返回当前实际值*/
	return pid->actual_val;
}

/**
 * @brief 速度PID算法实现
 * @param {_pid} *pid
 * @param {float} actual_val 实际值
 * @return 输出PID计算后的值
 */
float speed_pid_realize(_pid *pid, float actual_val)
{
	/*计算误差*/
	pid->err = pid->target_val - actual_val;

	if ((pid->err < 0.5f) && (pid->err > -0.5f)) // 假如以最大允许速度偏差允许1分钟，输出最大偏差半圈
	{
		pid->err = 0.0f;
	}

	pid->integral += pid->err; // 误差累积

	/*积分限幅*/
	if (pid->integral >= 1000)
	{
		pid->integral = 1000;
	}
	else if (pid->integral < -1000)
	{
		pid->integral = -1000;
	}

	/*PID算法实现*/
	pid->actual_val = pid->Kp * pid->err + pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);

	/*误差传递*/
	pid->err_last = pid->err;

	/*返回当前实际值*/
	return pid->actual_val;
}
