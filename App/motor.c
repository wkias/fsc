#include "include.h"

uint16 motor_pulse = 0;    //电机观测速度
uint16 expected_motor_out; //期望速度

//测速
void PIT1_IRQHandler(void)
{
  static int16 ftm_quad_values[3] = {0};
  static int16 wight[3] = {MOTOR_MEASURE_FILTER_WIGHT_0,
                           MOTOR_MEASURE_FILTER_WIGHT_1,
                           MOTOR_MEASURE_FILTER_WIGHT_2};
  //速度滤波
  for (char i = 1; i > -1; i--)
  {
    ftm_quad_values[i + 1] = ftm_quad_values[i];
  }
  ftm_quad_values[0] = ftm_quad_get(FTM2);
  //负值处理
  if (ftm_quad_values[0] < 0)
  {
    ftm_quad_values[0] = -ftm_quad_values[0];
  }
  motor_pulse = (int)(ftm_quad_values[0] * wight[0] +
                      ftm_quad_values[1] * wight[1] +
                      ftm_quad_values[2] * wight[2]); //权值滤波
  ftm_quad_clean(FTM2);
  PIT_Flag_Clear(PIT1); //清中断标志位
}

//电机调速
void motor()
{
  static float motor_param[3] = {MOTOR_PID_PARAMENTER_P,
                                 MOTOR_PID_PARAMENTER_I,
                                 MOTOR_PID_PARAMENTER_D};
  uint32 static motor_out;      //输出速度,上次输出速度
  int32 static motor_errors[3]; //本次速度偏差，上次偏差，前次偏差

  //速度误差
  motor_errors[0] = expected_motor_out - motor_pulse;

  motor_out += motor_param[0] * (motor_errors[0]) +
               motor_param[1] * (motor_errors[0] + motor_errors[1] + motor_errors[2]) +
               motor_param[2] * (motor_errors[0] - 2 * motor_errors[1] + motor_errors[2]); //二次差分，相当于给导数求导

  //输出速度阈值
  if (motor_out > 2000)
    motor_out = 2000;
  if (motor_out < 0)
    motor_out = 0;

  motor_errors[2] = motor_errors[1];
  motor_errors[1] = motor_errors[0];

  ftm_pwm_duty(FTM0, FTM_CH2, motor_out);

  PIT_Flag_Clear(PIT2);
}
