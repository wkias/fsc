#include "include.h"

// 中断服务函数
void carport(void)
{
    // 清标志位，运行回调函数
    PORT_FUNC(A, 25, go_home);
}

// 进出车库
void go_home()
{
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, SERVO_LEFT_LIMIT);
    DELAY_MS(1000);
}
