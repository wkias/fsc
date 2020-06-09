#include "include.h"
#define SERVO_BASE_POINT 4950 //3900—4700—5500

int zhidao1;
int zhidao2;
int wangdao1;
int wangdao2;

int left_circuit_flag = 0;
int right_circuit_flag = 0;

uint32 expected_servo_out;//期望输出
uint32 servo_out;//舵机实际输出（期望输出融合误差）
float ad_Turn_P_L = 0.3, ad_Turn_P_R = 0.3, ad_Turn_D_L = 1.2, ad_Turn_D_R = 1.2, ad_K_error = 1;

void servo()
{
    float midpoint_error;  //中线误差
    float lastpoint_error; //上次误差

    // ADC1_SE4a, PTE0   左电磁
    // ADC1_SE5a, PTE1   最左电磁
    // ADC1_SE6a, PTE2  右电磁
    // ADC1_SE7a, PTE3  最右电磁
    // ADC0_SE17, PTE24  左竖电磁
    // ADC0_SE18  PTE25  右竖电磁
    if (adc_val[2] > 950 && adc_val[0] > 950 && adc_val[5] < 100)
    {
        left_circuit_flag = 2;
    }
    if ((adc_val[5] > 100) )
    {
        left_circuit_flag = 3;
    }

    /*********丢线 *************/
    if (adc_val[0] < 50 && adc_val[2] < 50 && adc_val[1] < 50 && adc_val[3] > 150)
    {
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 850);
        expected_servo_out = 4950 + 850;
        systick_delay_ms(150); //100
    }
    if (adc_val[0] < 50 && adc_val[2] < 50 && adc_val[3] < 50 && adc_val[1] > 150)
    {
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 850);
        expected_servo_out = 4950 - 850;
        systick_delay_ms(150); //100
    }
    else
    {
        midpoint_error = (0.3 * adc_errors[1] + 0.7 * adc_errors[2]); //计算误差
        if (midpoint_error < 0)
            servo_out = SERVO_BASE_POINT +
                        (ad_Turn_P_R * midpoint_error * midpoint_error + 10) * midpoint_error +
                        ad_Turn_D_R * (midpoint_error - lastpoint_error); //在一个值左右变化，防止左右摆动幅度大
        else if (midpoint_error >= 0)
            servo_out = SERVO_BASE_POINT + 
                        (ad_Turn_P_L * midpoint_error * midpoint_error + 10) * midpoint_error + 
                        ad_Turn_D_L * (midpoint_error - lastpoint_error);
        lastpoint_error = midpoint_error; //记录上次误差

        //输出限幅
        if (servo_out < SERVO_BASE_POINT - 850)
            servo_out = SERVO_BASE_POINT - 850;
        if (servo_out > SERVO_BASE_POINT + 850)
            servo_out = SERVO_BASE_POINT + 850;

        ftm_pwm_duty(FTM1, FTM_CH0, servo_out);
        expected_servo_out = servo_out;
    }
}
