#include "include.h"

float64_t servo_out; //舵机PWM占空比
float64_t ratio = PARAMENTER_SERVO_MOTOR_RATIO;
float servo_errors[3] = {0}; //本次中线误差，上次中线误差，累计误差和
float servo_pid_param[3] = {SERVO_PID_PARAMENTER_P,
                                    SERVO_PID_PARAMENTER_I,
                                    SERVO_PID_PARAMENTER_D};
float servo_errors_wight[3] = {SERVO_ERRORS_WEIGHT_0,
                                        SERVO_ERRORS_WEIGHT_1,
                                        SERVO_ERRORS_WEIGHT_2};
float64_t servo_correct = 0; //舵机误差增量修正值
void servo()
{
    servo_errors[0] = servo_errors_wight[0] * adc_errors[0][0] +
                      servo_errors_wight[1] * adc_errors[0][1] +
                      servo_errors_wight[2] * adc_errors[0][2];
    //位置PID，中线误差修正
    servo_correct = servo_pid_param[0] * servo_errors[0] +
                    servo_pid_param[1] * servo_errors[2] +
                    servo_pid_param[2] * (servo_errors[0] - servo_errors[1]);
    servo_errors[1] = servo_errors[0];
    servo_errors[2] += servo_errors[0];
    servo_out = SERVO_BASE_POINT + servo_correct;

    //限幅输出
    servo_out = (servo_out > SERVO_LEFT_LIMIT) ? servo_out : SERVO_LEFT_LIMIT;
    servo_out = (servo_out < SERVO_RIGHT_LIMIT) ? servo_out : SERVO_RIGHT_LIMIT;
    ftm_pwm_duty(PORT_SERVO, FTM_CH0, servo_out);

    //根据舵机偏转幅度计算电机期望速度
    servo_correct = (servo_correct > 0) ? servo_correct : -servo_correct;
    expected_motor_out = MOTOR_VELOCITY_SUPERIOR_LIMIT - servo_correct * ratio;
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, expected_motor_out);
}
