#include "include.h"

int carport_flag;
void carport(void)
{
    uint8  n = 0;    //引脚号

    //PTA6
    n = 6;
    if(PORTA_ISFR & (1 << n))           //PTA6触发中断
    {
        PORTA_ISFR  = (1 << n);        //写1清中断标志位
        ftm_pwm_duty(FTM1, FTM_CH0, SERVO_LEFT_LIMIT);
        systick_delay_ms(200);
    }
}
