#include "include.h"

int line_speed;
uint16 expected_motor_out; //期望速度
uint16 motor_pulse = 0;    //电机观测速度
float motor_param_P = 1, motor_param_I = 3, motor_param_D = 0;

int16 ftm_quad_values[3] = {0};
void PIT1_IRQHandler(void)
{
  int8 i;
  int val;
  gpio_init(PTB22, GPO, 0);
  val = ftm_quad_get(FTM2) * 12.4; //获取FTM 正交解码 的脉冲数(负数表示反方向)
  if (val < 0)
    val = -val;           //负值处理
  for (i = 0; i < 2; i++) //速度滤波
  {
    ftm_quad_values[i] = ftm_quad_values[i + 1];
  }
  ftm_quad_values[2] = val;
  motor_pulse = (int)(ftm_quad_values[2] * 0.5 + ftm_quad_values[1] * 0.3 + ftm_quad_values[0] * 0.2); //权值滤波

  ftm_quad_clean(FTM2);
  PIT_Flag_Clear(PIT1); //清中断标志位
}

void motor();
void PIT2_IRQHandler()
{
  motor();
  PIT_Flag_Clear(PIT2);
}

void motor()
{
  unsigned int static motor_out[2];  //输出速度,上次输出速度
  signed int static motor_errors[3]; //本次速度偏差，上次偏差，前次偏差

  //速度误差
  motor_errors[0] = expected_motor_out - motor_pulse;
  
  motor_out[1] = motor_out[0];
  motor_out[0] = motor_param_P * (motor_errors[0] - motor_errors[1]) + motor_param_I * motor_errors[0] +
                 motor_param_D * (motor_errors[0] - 2 * motor_errors[1] + motor_errors[2]); //二次差分，相当于给导数求导

  //输出速度阈值
  if (motor_out[0] > 2000)
  {
    motor_out[0] = 2000;
  }
  if (motor_out[0] < 0)
  {
    motor_out[0] = 0;
  }

  motor_errors[2] = motor_errors[1];
  motor_errors[1] = motor_errors[0];

  ftm_pwm_duty(FTM0, FTM_CH2, motor_out[0]);
}
