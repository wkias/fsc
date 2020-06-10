#include "include.h"

int carport_flag;
void carport(void)
{
    led(LED_CARPORT, LED_ON);
    uint8 n = 6;               //引脚号PTA6
    if (PORTA_ISFR & (1 << n)) //PTA6触发中断
    {
        PORTA_ISFR = (1 << n); //写1清中断标志位
        ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_LEFT_LIMIT);
        systick_delay_ms(200);
    }
    led(LED_CARPORT, LED_OFF);
}
