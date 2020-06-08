#include "include.h"

int carport_flag;

void carport()
{
  if (gpio_get(PTC3)==1) //gpio_get(PTC3)==0
  {
    ftm_pwm_duty(FTM1, FTM_CH0, angle1);
    speed_djout = angle1;
    systick_delay_ms(time1);

    ftm_pwm_duty(FTM1, FTM_CH0, angle2); //600
    speed_djout = angle2;
    systick_delay_ms(time2);

    ftm_pwm_duty(FTM1, FTM_CH0, angle3);
    speed_djout = angle3;
    systick_delay_ms(time3);

    ftm_pwm_duty(FTM1, FTM_CH0, angle4);
    speed_djout = angle4;
    systick_delay_ms(time4);

    ftm_pwm_duty(FTM1, FTM_CH0, angle5);
    speed_djout = angle5;
    systick_delay_ms(time5);
  }
}