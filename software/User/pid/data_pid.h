#ifndef __DATA_PID_H
#define __DATA_PID_H


typedef struct
{
	float target_val; // 目标值
	float actual_val; // 实际值
	float err;		  // 当前误差
	float err_last;	  // 上一个误差
	float Kp, Ki, Kd; // 比例系数
	float integral;	  // 积分值
} _pid;

extern _pid pid_speed, pid_speed2;
extern _pid pid_location, pid_location2;

void PID_param_init(void);
void set_pid_target(_pid *pid, float temp_val);
float get_pid_target(_pid *pid);
void set_p_i_d(_pid *pid, float p, float i, float d);

float location_pid_realize(_pid *pid, float actual_val);
float speed_pid_realize(_pid *pid, float actual_val);

#endif /*__DATA_PID_H */
