#include "include.h"
int8 light_switcher = 1;

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

void rampway()
{
    disable_irq(PIT1_IRQn);
    disable_irq(PIT2_IRQn); //其他定时器关闭
    gpio_set(PORT_BEEPER, 1);
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_BASE_POINT);              //中线打死
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, MOTOR_VELOCITY_SUPERIOR_LIMIT); //速度最大
    DELAY_MS(1100);                                                   //上坡时检测到下坡时减速   800
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);                             //速度为零
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_RIGHT_LIMIT);             //向右打死
    DELAY_MS(800);
    gpio_set(PORT_BEEPER, 0);
}
