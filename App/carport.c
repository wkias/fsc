#include "include.h"
int8 ON_ROAD = 0;

// 中断服务函数
void carport(void)
{
    led(LED0, LED_ON);
    // 清标志位，运行回调函数
    PORT_FUNC(A, 25, go_from_home);
}

// 进出车库
void go_from_home()
{
    if (!ON_ROAD)
    {
        ON_ROAD = 1;
        gpio_set(PORT_BEEPER, 1);
        enable_irq(PIT1_IRQn);
        enable_irq(PIT2_IRQn);
        ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_LEFT_LIMIT);
        ftm_pwm_duty(PORT_MOTOR, FTM_CH2, MOTOR_VELOCITY_INFERIOR_LIMIT);
        DELAY_MS(1000);
        gpio_set(PORT_BEEPER, 0);
    }
    else
    {
        ON_ROAD = 0;
        gpio_set(PORT_BEEPER, 1);
        disable_irq(PIT1_IRQn);
        disable_irq(PIT2_IRQn);
        ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_BASE_POINT);
        ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);
        DELAY_MS(1000);
        gpio_set(PORT_BEEPER, 0);
        while (1)
            ;
    }
}
