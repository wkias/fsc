#include "include.h"

int line_speed;
uint16 ex_speed;
uint16 RightMotorPulse = 0; //目标速度、右电机测速
float ad_Speed_P = 1, ad_Speed_I = 3, ad_Speed_D = 0; //10,0.8,0//70,10,0//6   //1,3,0


int16 ftm_quad_values[3] = {0};
void PIT1_IRQHandler(void){
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
  RightMotorPulse = (int)(ftm_quad_values[2] * 0.5 + ftm_quad_values[1] * 0.3 + ftm_quad_values[0] * 0.2); //权值滤波

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
  unsigned int static ad_speed_out;  //输出实际速度
  signed int static ad_speed_error;  //速度误差
  signed int static ad_last_error_1; //上次偏差
  signed int static ad_last_error_2; //上上次偏差

  ad_speed_error = ex_speed - RightMotorPulse;

  if (ad_speed_out > 2000)
    ad_speed_out = 2000;
  if (ad_speed_out < 0)
    ad_speed_out = 0;

  if (gpio_get(PTC3) == 0)
  {
    carport_flag = 1;
  }

  if (bin_youhuandaoflag > 0 || bin_zuohuandaoflag > 0)
  {
    ex_speed = 1100; //750
  }

  if (sin_youhuandaoflag > 0 || sin_zuohuandaoflag > 0)
  {
    ex_speed = 850; //750
  }

  if ((line_speed == 1))
  {
    ex_speed = 800;
  }

  if (bin_youhuandaoflag == 0 && bin_zuohuandaoflag == 0 && sin_youhuandaoflag == 0 && sin_zuohuandaoflag == 0)
  {

    if ((speed_djout >= 4850 && speed_djout <= 5050))
    {
      ex_speed = zhidao1; //900,1000
    }
    else if ((speed_djout > 4750 && speed_djout < 4850) || (speed_djout < 5150 && speed_djout > 5050))
    {
      ex_speed = zhidao2; //800
    }
    else if ((speed_djout < 4750 && speed_djout > 4650) || (speed_djout < 5350 && speed_djout > 5150))
    {
      ex_speed = wangdao1; //750
    }
    else if (speed_djout <= 4650 || speed_djout >= 5350)
    {
      ex_speed = wangdao2; //700
    }
  }

  ad_speed_out = ad_Speed_P * (ad_speed_error - ad_last_error_1) + ad_Speed_I * ad_speed_error +
                 ad_Speed_D * (ad_speed_error - 2 * ad_last_error_1 + ad_last_error_2); //二次差分，相当于给导数求导

  ad_last_error_2 = ad_last_error_1;
  ad_last_error_1 = ad_speed_error;

  ftm_pwm_init(FTM0, FTM_CH2, 10000, ad_speed_out);
}
