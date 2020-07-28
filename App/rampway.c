#include "include.h"
void rampway()
{
    gpio_set(PORT_BEEPER, 1);
    DELAY_MS(800);//上坡时检测到下坡时减速
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);//速度为零
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_RIGHT_LIMIT);//向右打死
    DELAY_MS(800);
    gpio_set(PORT_BEEPER, 0);
}