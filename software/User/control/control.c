///*
// * @Date: 2023-07-14 13:48:43
// * @LastEditTime: 2023-07-17 17:18:17
// * @Description: 包含全部控制电机运动的函数
// */
//#include "control.h"
//#include "init.h"
//#include "bsp_encoder.h"
//#include "data_pid.h"
//#include "Fire_protocol.h"

//unsigned char location_control_count = 0; // 执行频率不需要那么高的用这个事件计数，用在中断中

//float MotorPWM = 0.0, Motor2PWM = 0.0;

//float speed_Outval, location_Outval;
//float speed2_Outval, location2_Outval;
//float Line_Outval = 0;
//int Turn_val;

//u8 Line_flag;
//u8 Spin_start_flag, Spin_succeed_flag, Stop_Flag;
//u8 stop_count, spin_count;

//u8 is_motor_en = 1; // 电机使能状态

//float g_fTargetJourney = 0;				   // 存放小车左右轮所需要走的路程和，单位cm
//float Motor_journey_cm, Motor2_journey_cm; // 存放当前轮子走过的路程，单位cm

///**
// * @brief 定时器7中断处理函数，同时为PID控制函数
// * @return
// */
//void TIM7_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
//	{
//		GetMotorPulse();
//		Motor_journey_cm = (g_lMotorPulseSigma / (30 * 11 * 4)) * (6.5 * 3.14);
//		Motor2_journey_cm = (g_lMotor2PulseSigma / (30 * 11 * 4)) * (6.5 * 3.14);

//		/*****上位机pid调试速度话用,实际运行时注释掉*****/

//		// if (is_motor_en == 1)
//		// {
//		// 	MotorPWM = speed_pid_control();
//		// 	Motor2PWM = speed2_pid_control();
//		// }
//		// MotorOutput(MotorPWM, Motor2PWM);
//		/******/

//		/******上位机调试位置速度串级PID时用，实际使用时注释掉******/

//		// if (is_motor_en == 1)
//		// {
//		// Location_Speed_control();
//		// 	MotorPWM = speed_Outval;
//		// 	Motor2PWM = speed2_Outval;
//		// 	MotorOutput(MotorPWM, Motor2PWM);
//		// }
//		/************/

//		if (Line_flag == 1) // 走直线时
//		{
//			// if ((Motor_journey_cm <= (g_fTargetJourney + 25)) && (Motor_journey_cm >= (g_fTargetJourney - 25)))
//			// {
//			// 	stop_count++;		   // stop_count不能超过256
//			// 	if (stop_count >= 100) // 100 * 20 = 2s  最少也要至少在目标位置停留1s  //可以时间判断放长点，以便刹车停稳
//			// 	{
//			// 		Line_flag = 0;
//			// 		Stop_Flag = 1; // 这个标志位可以用来判断是否执行下一阶段任务
//			// 		stop_count = 0;

//			// 		set_motor_disable();
//			// 		set_motor2_disable();
//			// 	}
//			// }
//			// else
//			// {
//			// 	Stop_Flag = 0;
//			// 	stop_count = 0;
//			// }

//			if (is_motor_en == 1) // 电机在使能状态下才进行控制处理
//			{
//				Location_Speed_control(); // 位置环速度环串级PID的输出是速度环输出的PWM值

//				// if (Line_Num == 0) // 每次回到线上需要补偿的时候，都将两个电机的累计脉冲数取平均值，这个也会有在转向后帮助回到线上的效果
//				// {
//				// 	long Pulse;

//				// 	Pulse = (g_lMotorPulseSigma + g_lMotor2PulseSigma) / 2;

//				// 	g_lMotorPulseSigma = Pulse; // 可能有时候这里加上个补偿会更好
//				// 	g_lMotor2PulseSigma = Pulse;
//				// }

//				// // 这个是灰度传感器的巡线补偿
//				// Line_Outval = Line_Num; // lineNum得在PWM的重装载值一半左右才会有明显的效果
//				MotorPWM = speed_Outval + Line_Outval;
//				Motor2PWM = speed2_Outval - Line_Outval;

//				MotorOutput(MotorPWM, Motor2PWM);
//			}
//		}

//		// 		if (Spin_start_flag == 1) // 转向时
//		// 		{
//		// 			if (is_motor_en == 1) // 电机在使能状态下才进行控制处理
//		// 			{
//		// 				Location_Speed_control(); // 位置环速度环串级PID的输出是速度环输出的PWM值

//		// 				MotorPWM = speed_Outval;
//		// 				Motor2PWM = speed2_Outval;

//		// 				spin_count++;
//		// 				if (spin_count >= 100) // 20ms进入一次   100*20 = 2s，以能过够完成倒转时间为下限，应该已经倒转完毕了
//		// 				{
//		// 					Spin_start_flag = 0;
//		// 					spin_count = 0;

//		// 					// 转向有点问题，转完之后还一直转,暂时用下面两句解决
//		// 					MotorPWM = 0;
//		// 					Motor2PWM = 0;
//		// 				}

//		// 				MotorOutput(MotorPWM, Motor2PWM);
//		// 			}
//		// 		}

//		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//	}
//}

//void Car_go(int32_t location_cm) // 直走函数
//{
//	float Car_location;

//	//	if(location_cm < 0)
//	//	{
//	//		LineNumToggleFlag = 1;
//	//	}
//	//	else LineNumToggleFlag = 0;

//	Motor_journey_cm = 0;
//	Motor2_journey_cm = 0;

//	g_fTargetJourney = location_cm; // 防止长时间PID控制用

//	// 如果巡线效果不好就将3.142加大
//	Car_location = (location_cm / (6.5 * 3.14)) * (30 * 4 * 11); // Car_location 将  location_cm 转换为对应的脉冲数   g_fTargetJourney = 要转多少圈 * 1圈的脉冲数
//	// 小车位置直接用一个电机的脉冲数累积就好，转向时不计数，开始一个位置前直接清零。
//	// 打滑导致一个轮比另一个轮转位置不一样咋办,用“巡线环“弥补就好，转向就用“转向环”

//	set_pid_target(&pid_location, Car_location);
//	set_pid_target(&pid_location2, Car_location);

//	set_motor_enable(); // 使能电机控制PWM输出

//	g_lMotorPulseSigma = 0;
//	g_lMotor2PulseSigma = 0;
//}

///******转向完成时自动将  Spin_start_flag == 0 、 Spin_succeed_flag == 1  ********/
///*转角有左转90，右转90，和转180三种情况。*/

//void spin_Turn(spin_dir_t zhuanxiang) // 传入小车的轮距(mm) 175mm  //其实转向环并不需要很精准，转弯后直接用直走时的巡线函数回正车身就好
//{

//	float spin90_val;
//	float Car_Turn_val;

//	Motor_journey_cm = 0;
//	Motor2_journey_cm = 0;

//	spin90_val = 0.25 * 3.1416 * LUN_JU;

//	/****转弯后不循线可以调转向系数**********/
//	if (zhuanxiang == left_90) // openmv识别到需要往左边病房走
//	{
//		Car_Turn_val = (spin90_val / (6.5 * 3.142)) * (56 * 4 * 11);
//		Car_Turn_val = 0.95 * Car_Turn_val; // 90*0.94 = 84.6   //惯性影响，导致转弯比理论设定的多。直接设90度接下来的巡线就寻不回来了
//	}
//	else if (zhuanxiang == right_90) // openmv识别到需要往右边病房走
//	{
//		Car_Turn_val = -(spin90_val / (6.5 * 3.142)) * (56 * 4 * 11);
//		Car_Turn_val = 0.98 * Car_Turn_val; // 90*0.96 = 86.4    //惯性影响，导致转弯比理论设定的多。 接下来的巡线可能就寻不回来了
//	}
//	else if (zhuanxiang == back_180)
//	{
//		Car_Turn_val = -(spin90_val / (6.5 * 3.142)) * (56 * 4 * 11);
//		Car_Turn_val = 0.98 * Car_Turn_val; // 同理
//		Car_Turn_val = 2 * Car_Turn_val;	// 0.96*180 = 175.5
//	}

//	set_pid_target(&pid_location, -Car_Turn_val);
//	set_pid_target(&pid_location2, Car_Turn_val);

//	g_lMotorPulseSigma = 0;
//	g_lMotor2PulseSigma = 0;

//	set_motor_enable(); // 使能电机控制PWM输出
//}

///*********************各PID**********************/
///****速度环位置环串级PID控制*****/

///**
// * @brief 速度环位置环串级PID控制
// * @return
// */
//void Location_Speed_control(void) // 原地转向可以直接 调用这个
//{
//	// mpu_dmp_get_data放在这会影响到编码器脉冲的获取。
//	if (is_motor_en == 1) // 电机在使能状态下才进行控制处理
//	{
//		location_control_count++;
//		if (location_control_count >= 2)
//		{
//			location_control_count = 0;

//			location_Outval = location_pid_control();
//			location2_Outval = location2_pid_control();
//		}

//		set_pid_target(&pid_speed, location_Outval);   // 每次都必须有位置环的值     //调试速度环PID时取消这两句
//		set_pid_target(&pid_speed2, location2_Outval); // 每次都必须有位置环的值

//		speed_Outval = speed_pid_control(); // 要是电机转向不符合预期，就在这两句里取反数值
//		speed2_Outval = speed2_pid_control();
//	}
//}

///**
// * @brief 电机1位置环PID控制
// * @return PID计算后的PWM
// */
//float location_pid_control(void)
//{
//	float cont_val = 0.0;
//	int32_t actual_location;

//	actual_location = g_lMotorPulseSigma; // 1圈 = 2464个脉冲 = 56*11*4  //这里位置用圈数代替。

//	cont_val = location_pid_realize(&pid_location, actual_location);

//	// 还没加串级pID之前，位置环的cont_val对应PWM。 改成串级PID后，位置环的cont_val对应目标速度

//	/* 目标速度上限处理 */
//	if (cont_val > TARGET_SPEED_MAX)
//	{
//		cont_val = TARGET_SPEED_MAX;
//	}
//	else if (cont_val < -TARGET_SPEED_MAX)
//	{
//		cont_val = -TARGET_SPEED_MAX;
//	}

//	// #if defined(PID_ASSISTANT_EN)
//	// 	set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1); // 给通道 1 发送实际值
//	// 																		// BlueSignal_Toggle;  //可以进来
//	// #endif
//	return cont_val;
//}

///**
// * @brief 电机1速度环PID控制
// * @return PID计算后的速度
// */
//float speed_pid_control(void)
//{
//	float cont_val = 0.0; // 当前控制值
//	int32_t actual_speed;

//	actual_speed = ((float)g_nMotorPulse * 1000.0 * 60.0) / (ENCODER_TOTAL_RESOLUTION * REDUCTION_RATIO * SPEED_PID_PERIOD);

//	cont_val = speed_pid_realize(&pid_speed, actual_speed); // 进行PID计算

//	// #if defined(PID_ASSISTANT_EN)
//	// 	set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1); // 给通道1发送实际值
//	// #endif

//	return cont_val;
//}

///**
// * @brief 电机2位置环PID控制
// * @return PID计算后的PWM
// */
//float location2_pid_control(void)
//{
//	float cont_val = 0.0;
//	int32_t actual_location;

//	actual_location = g_lMotor2PulseSigma; // 1圈 = 2464个脉冲 = 56*11*4  //这里位置用圈数代替。

//	cont_val = location_pid_realize(&pid_location2, actual_location);

//	// 改成串级PID后，位置换的cont_val对应目标速度

//	// 目标速度限幅
//	/* 目标速度上限处理 */
//	if (cont_val > TARGET_SPEED_MAX)
//	{
//		cont_val = TARGET_SPEED_MAX;
//	}
//	else if (cont_val < -TARGET_SPEED_MAX)
//	{
//		cont_val = -TARGET_SPEED_MAX;
//	}

//	//	  #if defined(PID_ASSISTANT_EN)
//	//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1);                // 给通道 1 发送实际值
//	//		//set_computer_value(SEND_TARGET_CMD, CURVES_CH1,&TargetSpeed, 1);                // 给通道 1 发送目标值？这个是目标控制值，整定参数时不用发送，否则无法在上位机上设置
//	//  #endif

//	return cont_val;
//}

///**
// * @brief 电机2速度环PID控制
// * @return PID计算后的速度
// */
//float speed2_pid_control(void)
//{

//	float cont_val = 0.0; // 当前控制值
//	int32_t actual_speed;

//	actual_speed = ((float)g_nMotor2Pulse * 1000.0 * 60.0) / (ENCODER_TOTAL_RESOLUTION * REDUCTION_RATIO * SPEED_PID_PERIOD);

//	cont_val = speed_pid_realize(&pid_speed2, actual_speed); // 进行 PID 计算

//	// #if defined(PID_ASSISTANT_EN)
//	// 	set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1); // 给通道 1 发送实际值
//	// #else
//	// #endif

//	return cont_val;
//}

///**
// * @brief 根据pwm控制速度及方向
// * @param {int} nMotorPwm 电机1PWM
// * @param {int} nMotor2Pwm 电机2PWM
// * @return
// */
//void MotorOutput(int nMotorPwm, int nMotor2Pwm)
//{
//	if (nMotorPwm >= 0)
//	{
//		set_motor_direction(MOTOR_FWD);
//	}
//	else
//	{
//		nMotorPwm = -nMotorPwm;
//		set_motor_direction(MOTOR_REV);
//	}

//	nMotorPwm = (nMotorPwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotorPwm; // 速度上限处理

//	if (nMotor2Pwm >= 0)
//	{
//		set_motor2_direction(MOTOR_FWD);
//	}
//	else
//	{
//		nMotor2Pwm = -nMotor2Pwm;
//		set_motor2_direction(MOTOR_REV);
//	}
//	nMotor2Pwm = (nMotor2Pwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotor2Pwm; // 速度上限处理

//	set_motor_speed(nMotorPwm, nMotor2Pwm);
//}

///**
// * @brief 设置电机速度
// * @param {uint16_t} v 速度1（占空比）
// * @param {uint16_t} v2 速度2（占空比）
// * @return
// */
//void set_motor_speed(uint16_t v, uint16_t v2)
//{
//	SET_COMPAER(v);
//	SET2_COMPAER(v2);
//}

///**
// * @brief 设置电机1方向
// * @param {motor_dir_t} dir
// * @return {*}
// */
//void set_motor_direction(motor_dir_t dir)
//{
//	if (dir == MOTOR_FWD)
//	{
//		L_IN1(High);
//		L_IN2(Low);
//	}
//	else
//	{
//		L_IN1(Low);
//		L_IN2(High);
//	}
//}

///**
// * @brief 设置电机2方向
// * @param {motor_dir_t} dir
// * @return
// */
//void set_motor2_direction(motor_dir_t dir)
//{
//	if (dir == MOTOR_FWD)
//	{
//		R_IN1(High);
//		R_IN2(Low);
//	}
//	else
//	{
//		R_IN1(Low);
//		R_IN2(High);
//	}
//}

///**
// * @brief 使能电机
// * @return
// */
//void set_motor_enable(void)
//{
//	is_motor_en = 1;
//	MOTOR_ENABLE();
//}

///**
// * @brief 禁用电机
// * @return
// */
//void set_motor_disable(void)
//{
//	is_motor_en = 0;
//	MOTOR_DISABLE();
//}
