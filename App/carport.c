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
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_BASE_POINT);//舵机中线打死
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);
   // DELAY_MS(motor_pulse / 8);//减速
    DELAY_MS(800);
    gpio_set(PORT_BEEPER, 0);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH3, MOTOR_VELOCITY_BASE_POINT);//倒车
    DELAY_MS(800);
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_RIGHT_LIMIT);//向右打死
    DELAY_MS(800);
    
    // DELAY_MS(300000/motor_pulse );
    
    ftm_pwm_duty(PORT_MOTOR, FTM_CH3, 0);
}
