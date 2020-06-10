#include "include.h"

uint16 motor_pulse = 0;        //电机观测速度
uint16 expected_motor_out = 0; //期望速度

//编码器测速
void coder(void)
{
  PIT_Flag_Clear(PIT1); //清中断标志位
  static int16 ftm_quad_values[3] = {0};
  static int16 wight[3] = {CODER_FILTER_WIGHT_0,
                           CODER_FILTER_WIGHT_1,
                           CODER_FILTER_WIGHT_2};

  for (char i = 1; i > -1; i--)
  {
    ftm_quad_values[i + 1] = ftm_quad_values[i];
  }
  ftm_quad_values[0] = ftm_quad_get(PORT_CODER);
  ftm_quad_clean(PORT_CODER);

  //负值处理
  ftm_quad_values[0] = (ftm_quad_values[0] > 0) ? ftm_quad_values[0] : -ftm_quad_values[0];

  //权值滤波
  motor_pulse = (int)(ftm_quad_values[0] * wight[0] +
                      ftm_quad_values[1] * wight[1] +
                      ftm_quad_values[2] * wight[2]);
}

//电机调速
void motor()
{
  PIT_Flag_Clear(PIT2);

  //PID参数，可在settings.h中更改
  static float motor_param[3] = {MOTOR_PID_PARAMENTER_P,
                                 MOTOR_PID_PARAMENTER_I,
                                 MOTOR_PID_PARAMENTER_D};
  static uint32 motor_out;      //输出速度,上次输出速度
  static int32 motor_errors[3]; //本次速度偏差，上次偏差，前次偏差

  //速度误差
  motor_errors[0] = expected_motor_out - motor_pulse;

  //增量PID，速度误差修正
  motor_out += motor_param[0] * (motor_errors[0] - motor_errors[1]) +
               motor_param[1] * motor_errors[0] +
               motor_param[2] * (motor_errors[0] - 2 * motor_errors[1] + motor_errors[2]); //二次差分，相当于给导数求导

  //限速输出
  motor_out = MAX(motor_out, MOTOR_VELOCITY_SUPERIOR_LIMIT);
  motor_out = MIN(motor_out, MOTOR_VELOCITY_INFERIOR_LIMIT);
  ftm_pwm_duty(FTM0, FTM_CH2, motor_out);

  motor_errors[2] = motor_errors[1];
  motor_errors[1] = motor_errors[0];
}
