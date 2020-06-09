#include "include.h"

int zhidao1;
int zhidao2;
int wangdao1;
int wangdao2;

int left_circuit_flag = 0;
int right_circuit_flag = 0;

uint32 expected_servo_out; //期望输出
uint32 servo_out;          //舵机实际输出（期望输出融合误差）

void servo()
{
    float servo_errors[2] = {0}; //本次误差，上次误差
    static float servo_param[3] = {SERVO_PID_PARAMENTER_P,
                                   SERVO_PID_PARAMENTER_I,
                                   SERVO_PID_PARAMENTER_D};

    servo_errors[0] = (0.3 * adc_errors[1] + 0.7 * adc_errors[2]); //计算误差
    if (servo_errors[0] < 0)
        servo_out = SERVO_BASE_POINT +
                    (SERVO_PID_PARAMENTER_P * servo_errors[0] * servo_errors[0] + 10) * servo_errors[0] +
                    SERVO_PID_PARAMENTER_D * (servo_errors[0] - servo_errors[1]);
    else if (servo_errors[0] >= 0)
        servo_out = SERVO_BASE_POINT +
                    (SERVO_PID_PARAMENTER_P * servo_errors[0] * servo_errors[0] + 10) * servo_errors[0] +
                    SERVO_PID_PARAMENTER_D * (servo_errors[0] - servo_errors[1]);
    servo_errors[1] = servo_errors[0]; //记录上次误差

    //输出限幅
    if (servo_out < SERVO_BASE_POINT - 850)
        servo_out = SERVO_BASE_POINT - 850;
    if (servo_out > SERVO_BASE_POINT + 850)
        servo_out = SERVO_BASE_POINT + 850;

    ftm_pwm_duty(FTM1, FTM_CH0, servo_out);
    expected_servo_out = servo_out;
}
}
