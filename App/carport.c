#include "include.h"
int8 ON_ROAD = 0;

// 中断服务函数
void carport(void)
{
    // 清标志位，运行回调函数
    PORT_FUNC(B, 0, go_home);
}

// 进入车库
void go_home()
{
    gpio_set(PORT_BEEPER, 1);
    disable_irq(PIT1_IRQn);
    disable_irq(PIT2_IRQn);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);
    DELAY_MS(1000);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH3, MOTOR_VELOCITY_BASE_POINT);
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_LEFT_LIMIT);
    gpio_set(PORT_BEEPER, 0);
    DELAY_MS(3000);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH3, 0);
}
