#include "include.h"

int8 direction = 0; // 舵机偏差方向标记
float32_t servo_pid_param[3] = {SERVO_PID_PARAMETER_P,
                                SERVO_PID_PARAMETER_I,
                                SERVO_PID_PARAMETER_D};
float32_t servo_bias_wight[3] = {SERVO_BIAS_WEIGHT_0,
                                 SERVO_BIAS_WEIGHT_1,
                                 SERVO_BIAS_WEIGHT_2};
float32_t servo_bias[3] = {0}; // 本次中线误差，上次中线误差，累计误差和
float32_t servo_correct = 0;   // 舵机误差增量修正值
float32_t servo_out = 0;       // 舵机PWM占空比
float32_t ratio = ((float32_t)MOTOR_VELOCITY_INTERVAL / SERVO_DUTY_INTERVAL_LIMIT);
int8 LOST_IN_FRANXX = 0; // 丢线标记
int8 rotary_road = 0;    // 环岛标记
int8 rotary_road_switcher = 1;

void servo()
{
    // 环岛
    if (rotary_road_switcher)
    {
#ifndef THE_SECONDARY
        if (adc_val[0][1] > AD_BRUST_THRESHOLD || adc_val[0][2] > AD_BRUST_THRESHOLD || adc_val[0][3] > AD_BRUST_THRESHOLD || adc_val[0][4] > AD_BRUST_THRESHOLD)
        {
            if ((adc_val[0][0] > VERTICAL_INDUCTOR_THRESHOLD_MAX && adc_val[0][5] < VERTICAL_INDUCTOR_THRESHOLD_MIN) && rotary_road == 0) // 环道
            {
                round_in_circle(-1); //左
            }
            else if ((adc_val[0][0] < VERTICAL_INDUCTOR_THRESHOLD_MIN && adc_val[0][5] > VERTICAL_INDUCTOR_THRESHOLD_MAX) && rotary_road == 0)
            {
                round_in_circle(1); //右
            }
        }
#else
        if (adc_val[0][1] > AD_BRUST_THRESHOLD || adc_val[0][2] > AD_BRUST_THRESHOLD || adc_val[0][3] > AD_BRUST_THRESHOLD || adc_val[0][4] > AD_BRUST_THRESHOLD)
        {
            round_in_circle(-1); //左
        }
#endif
    }
    // 丢线
    if (adc_val[0][1] < LOST_IN_FRANXX_THRESHOLD_MIN && adc_val[0][2] < LOST_IN_FRANXX_THRESHOLD_MIN && (adc_val[0][4] > LOST_IN_FRANXX_THRESHOLD_MAX || LOST_IN_FRANXX == 1) || rotary_road == 1)
    {
        servo_out = SERVO_RIGHT_LIMIT;
        LOST_IN_FRANXX = 1;
    }
    else if ((adc_val[0][1] > LOST_IN_FRANXX_THRESHOLD_MAX || LOST_IN_FRANXX == -1) && adc_val[0][3] < LOST_IN_FRANXX_THRESHOLD_MIN && adc_val[0][4] < LOST_IN_FRANXX_THRESHOLD_MIN || rotary_road == -1)
    {
        servo_out = SERVO_LEFT_LIMIT;
        LOST_IN_FRANXX = -1;
    }
    else
    {
        gpio_set(PORT_BEEPER, 0);
        LOST_IN_FRANXX = 0;
        // 加权偏差
        servo_bias[0] = servo_bias_wight[0] * adc_bias[0][0] +
                        servo_bias_wight[1] * adc_bias[0][1] +
                        servo_bias_wight[2] * adc_bias[0][2];

        // 位置PID，中线误差修正
        direction = (servo_bias[0] > 0) ? 1 : -1;
        direction = rotary_road ? rotary_road : direction;
        servo_correct = servo_pid_param[0] * servo_bias[0] * servo_bias[0] * direction + // 二次动态P，以适应大小环道不同的角度
                        servo_pid_param[2] * (servo_bias[0] - servo_bias[1]) * (servo_bias[0] - servo_bias[1]) * direction;
        servo_correct /= 100;
        servo_bias[1] = servo_bias[0];
        servo_out = SERVO_BASE_POINT + servo_correct;
    }
    rotary_road = 0;

    // 限幅输出
    servo_out = (servo_out > SERVO_LEFT_LIMIT) ? servo_out : SERVO_LEFT_LIMIT;
    servo_out = (servo_out < SERVO_RIGHT_LIMIT) ? servo_out : SERVO_RIGHT_LIMIT;
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, servo_out);

    // 根据舵机偏转幅度计算电机期望速度
    expected_motor_out = SERVO_BASE_POINT - servo_out; // 期望输出暂时作中间变量
    expected_motor_out = (expected_motor_out > 0) ? expected_motor_out : -expected_motor_out;
#ifdef SIGMOID
    expected_motor_out = (SERVO_DUTY_INTERVAL_LIMIT - expected_motor_out) / SERVO_DUTY_INTERVAL_LIMIT * 10 - 5;
    expected_motor_out = (MOTOR_VELOCITY_SUPERIOR_LIMIT - MOTOR_VELOCITY_INFERIOR_LIMIT) / (1 + expl(-expected_motor_out)) + MOTOR_VELOCITY_INFERIOR_LIMIT;
#else
    expected_motor_out = MOTOR_VELOCITY_BASE_POINT - expected_motor_out * ratio;
#endif
    expected_motor_out = (SERVO_BASE_POINT - servo_out < SERVO_DUTY_INTERVAL_LIMIT / 2) ? MOTOR_VELOCITY_SUPERIOR_LIMIT : expected_motor_out;
    expected_motor_out = (expected_motor_out > MOTOR_VELOCITY_SUPERIOR_LIMIT) ? MOTOR_VELOCITY_SUPERIOR_LIMIT : expected_motor_out;
    expected_motor_out = (expected_motor_out < MOTOR_VELOCITY_INFERIOR_LIMIT) ? MOTOR_VELOCITY_INFERIOR_LIMIT : expected_motor_out;
}

void round_in_circle(int8 i)
{
    rotary_road = i;
    gpio_set(PORT_BEEPER, 1);
    DELAY_MS(rotary_road_time);
    rotary_road_switcher = 0;
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, (i == 1) ? SERVO_RIGHT_LIMIT : SERVO_LEFT_LIMIT);
    DELAY_MS(500);
    gpio_set(PORT_BEEPER, 0);
}
