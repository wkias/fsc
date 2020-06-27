#include "include.h"

int8 direction = 0; //舵机偏差正负号标记-方向标记
float32_t servo_pid_param[3] = {SERVO_PID_PARAMETER_P,
                                SERVO_PID_PARAMETER_I,
                                SERVO_PID_PARAMETER_D};
float32_t servo_bias_wight[3] = {SERVO_BIAS_WEIGHT_0,
                                 SERVO_BIAS_WEIGHT_1,
                                 SERVO_BIAS_WEIGHT_2};
float32_t servo_bias[3] = {0}; //本次中线误差，上次中线误差，累计误差和
float32_t servo_correct = 0;   //舵机误差增量修正值
float32_t servo_out = 0;       //舵机PWM占空比
float32_t ratio = ((float32_t)MOTOR_VELOCITY_INTERVAL / SERVO_DUTY_INTERVAL_LIMIT);
int8 LOST_IN_FRANXX = 0; //丢线标记
int8 rotary_road = 0;    //环岛标记

void servo()
{
    //丢线
    if (adc_val[0][1] < 100 && adc_val[0][2] < 100 && adc_val[0][3] < 100 && (adc_val[0][4] > 100 || LOST_IN_FRANXX == 1))
    {
        servo_out = SERVO_RIGHT_LIMIT;
        LOST_IN_FRANXX = 1;
    }
    else if ((adc_val[0][1] > 100 || LOST_IN_FRANXX == -1) && adc_val[0][2] < 100 && adc_val[0][3] < 100 && adc_val[0][4] < 100)
    {
        servo_out = SERVO_LEFT_LIMIT;
        LOST_IN_FRANXX = -1;
    }
    // else if (adc_bias[0][0] > 100)
    // {
    //     if (rotary_road != 0 && rotary_road % 2 != 0)
    //     {
    //         servo_out = SERVO_LEFT_LIMIT;
    //     }
    //     rotary_road -= 1;
    // }
    // else if (adc_bias[0][0] < -100)
    // {
    //     if (rotary_road != 0 && rotary_road % 2 != 0)
    //     {
    //         servo_out = SERVO_RIGHT_LIMIT;
    //     }
    //     rotary_road += 1;
    // }
    else if (adc_val[0][3] > 700 && adc_val[0][4] > 700)
    {
        if (adc_val[0][0] > adc_val[0][5])
        {
            servo_out = SERVO_LEFT_LIMIT;
            DELAY_MS(100);
        }
        else
        {
            servo_out = SERVO_RIGHT_LIMIT;
            DELAY_MS(100);
        }
    }
    else
    {
        LOST_IN_FRANXX = 0;
        rotary_road = 0;
        //加权偏差
        servo_bias[0] = servo_bias_wight[0] * adc_bias[0][0] * adc_bias_gradient[0] +
                        servo_bias_wight[1] * adc_bias[0][1] +
                        servo_bias_wight[2] * adc_bias[0][2];

        //位置PID，中线误差修正
        direction = (servo_bias[0] > 0) ? 1 : -1;
        servo_correct = servo_pid_param[0] * servo_bias[0] * servo_bias[0] * direction + //二次动态P，以适应大小环道不同的角度
                        servo_pid_param[2] * (servo_bias[0] - servo_bias[1]) * (servo_bias[0] - servo_bias[1]);
        servo_correct /= 30;
        servo_bias[1] = servo_bias[0];
        servo_out = SERVO_BASE_POINT + servo_correct;
    }

    //限幅输出
    servo_out = (servo_out > SERVO_LEFT_LIMIT) ? servo_out : SERVO_LEFT_LIMIT;
    servo_out = (servo_out < SERVO_RIGHT_LIMIT) ? servo_out : SERVO_RIGHT_LIMIT;
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, servo_out);

    //根据舵机偏转幅度计算电机期望速度
    expected_motor_out = SERVO_BASE_POINT - servo_out; //期望输出暂时作中间变量
    expected_motor_out = (expected_motor_out > 0) ? expected_motor_out : -expected_motor_out;
    expected_motor_out = MOTOR_VELOCITY_BASE_POINT - expected_motor_out * ratio;
    expected_motor_out = (expected_motor_out > MOTOR_VELOCITY_SUPERIOR_LIMIT) ? MOTOR_VELOCITY_SUPERIOR_LIMIT : expected_motor_out;
    expected_motor_out = (expected_motor_out < MOTOR_VELOCITY_INFERIOR_LIMIT) ? MOTOR_VELOCITY_INFERIOR_LIMIT : expected_motor_out;
}

#ifdef INDUCTOR_CENTER_DISTANCE
float64_t arctan(float64_t x)
{
    float64_t mult, sum, xx;
    sum = 0;
    if (x == 1)
    {
        return PI / 4;
    }
    if (x == -1)
    {
        return -PI / 4;
    }

    mult = ((x > 1 || x < -1) ? 1 / x : x);
    xx = mult * mult;

    for (int i = 1; i < 200; i += 2)
    {
        sum += mult * ((i + 1) % 4 == 0 ? -1 : 1) / i;
        mult *= xx;
    }
    if (x > 1 || x < -1)
    {
        return PI / 2 - sum;
    }
    else
    {
        return sum;
    }
}
#endif
