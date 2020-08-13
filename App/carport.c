#include "include.h"
int8 light_switcher = 1;

// 中断服务函数
void carport(void)
{
    // 清标志位，运行回调函数
    PORT_FUNC(B, 0, go_home);
}

void go_out()
{
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_RIGHT_LIMIT);
    DELAY_MS(100);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, MOTOR_VELOCITY_BASE_POINT);
    DELAY_MS(1000);
}

// 进入车库
void go_home()
{
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH3, 1000);                   //倒转减速
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_RIGHT_LIMIT - 30); //向右
    DELAY_MS(300);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH3, 0);
    DELAY_MS(5000);
    gpio_set(PORT_BEEPER, 0);
    while (1)
        ;
}

void rampway()
{
    disable_irq(PIT1_IRQn);
    disable_irq(PIT2_IRQn); //其他定时器关闭
    gpio_set(PORT_BEEPER, 1);
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_BASE_POINT);                    //中线打死
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, MOTOR_VELOCITY_SUPERIOR_LIMIT + 400); //速度最大
    gpio_set(PORT_BEEPER, 0);
    while (1)
    {
        if (gpio_get(PORT_REED_SWITCHER) == 1) //干簧管入库
        {
            go_home();
        }
    }
}
