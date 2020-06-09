#include "include.h"
#define duoji_center 4950 //3900—4700—5500

int zhidao1;
int zhidao2;
int wangdao1;
int wangdao2;

int time1;
int time2;
int time3;
int time4;
int time5;

int angle1;
int angle2;
int angle3;
int angle4;
int angle5;

int sin_youhuandaoflag = 0;
int sin_zuohuandaoflag = 0;
int bin_zuohuandaoflag = 0;
int bin_youhuandaoflag = 0;

uint32 ad_Turn_PWMOUT_TOTAL;//PWM输出总量=PD运算后的PWM+舵机中值
float ad_lastlasterror, ad_lasterror;
float ad_fDirectionControlOut; //方向控制输出
float speed_djout;
float ad_Turn_P_L = 0.3, ad_Turn_P_R = 0.3, ad_Turn_D_L = 1.2, ad_Turn_D_R = 1.2, ad_K_error = 1;


void servo()
{
    float midpoint_error;  //中线误差
    float lastpoint_error; //上次误差

    //s-right-in
    if (adc_val[2] > 950 && adc_val[0] > 950 && adc_val[5] < 100 && sin_youhuandaoflag == 1)
    {
        gpio_init(PTB22, GPO, 1);
        sin_youhuandaoflag = 2;
    }

    if ((adc_val[5] > 100) && (sin_youhuandaoflag == 2))
    {
        sin_youhuandaoflag = 3;

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 800);
        speed_djout = 4950 + 800;
        systick_delay_ms(300); //200

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 800);
    }
    if (sin_youhuandaoflag == 3 && adc_val[4] > 300)
    {
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 550);
        speed_djout = 4950 + 550;
        systick_delay_ms(170);
    }

    if (adc_val[2] > 950 && adc_val[0] > 950 && adc_val[5] < 100 && bin_youhuandaoflag == 1)
    {
        bin_youhuandaoflag = 2;
        //Dis_num(80,6,2);
    }

    if ((adc_val[5] > 100) && (bin_youhuandaoflag == 2)) //150
    {
        //gpio_init  (PTB22, GPO, 1);
        bin_youhuandaoflag = 3;

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 800);
        speed_djout = 4950 + 800;
        systick_delay_ms(200);

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 800);
    }
    if (bin_youhuandaoflag == 3 && adc_val[4] > 250)
    {

        gpio_init(PTB22, GPO, 1);

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 450);
        speed_djout = 4950 + 450;
        systick_delay_ms(200); //250

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 300);
        speed_djout = 4950 - 300;
        systick_delay_ms(100);
        bin_youhuandaoflag = 0;
    }

    if (adc_val[0] > 950 && adc_val[2] > 950 && adc_val[4] < 100 && sin_zuohuandaoflag == 1)
    {
        gpio_init(PTB22, GPO, 1);
        sin_zuohuandaoflag = 2;
    }

    if ((adc_val[4] > 100) && (sin_zuohuandaoflag == 2))
    {
        sin_zuohuandaoflag = 3;
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 850);
        speed_djout = 4950 - 850;
        systick_delay_ms(300);
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 850);
    }
    if (sin_zuohuandaoflag == 3 && adc_val[5] > 200)
    {
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 600);
        speed_djout = 4950 - 600;
        systick_delay_ms(240);
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 300);
        speed_djout = 4950 + 300;
        systick_delay_ms(80);
    }

    if ((adc_val[0] > 700) && (adc_val[2] > 550) && (adc_val[4] > 250)) //b-zuo
    {
        gpio_init(PTB22, GPO, 1);
        bin_zuohuandaoflag = 1;

        pit_init_ms(PIT3, 5000);
    }

    if (adc_val[0] > 700 && adc_val[2] > 700 && adc_val[4] < 90 && bin_zuohuandaoflag == 1)
    {
        bin_zuohuandaoflag = 2;
    }

    if ((adc_val[4] > 80) && (bin_zuohuandaoflag == 2)) //120
    {
        bin_zuohuandaoflag = 3;

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 850);
        speed_djout = 4950 - 850;
        systick_delay_ms(200);

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 850);
    }
    if (bin_zuohuandaoflag == 3 && adc_val[5] > 250)
    {
        gpio_init(PTB22, GPO, 1);

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 500); //520
        speed_djout = 4950 - 500;
        systick_delay_ms(200); //250

        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 300);
        speed_djout = 4950 - 300;
        systick_delay_ms(80);

        bin_zuohuandaoflag = 0;
    }

    /*********丢线 *************/
    if (adc_val[0] < 50 && adc_val[2] < 50 && adc_val[1] < 50 && adc_val[3] > 150)
    {
        line_speed = 1;
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 + 850);
        speed_djout = 4950 + 850;
        systick_delay_ms(150); //100
        line_speed = 0;
    }
    if (adc_val[0] < 50 && adc_val[2] < 50 && adc_val[3] < 50 && adc_val[1] > 150)
    {
        line_speed = 1;
        ftm_pwm_duty(FTM1, FTM_CH0, 4950 - 850);
        speed_djout = 4950 - 850;
        systick_delay_ms(150); //100
        line_speed = 0;
    }
    else
    {
        midpoint_error = (0.3 * adc_errors[1] + 0.7 * adc_errors[2]);                                                                                                                 //计算误差     中线误差
        if (midpoint_error < 0)                                                                                                                                             //you
            ad_Turn_PWMOUT_TOTAL = duoji_center + (ad_Turn_P_R * midpoint_error * midpoint_error + 10) * midpoint_error + ad_Turn_D_R * (midpoint_error - lastpoint_error); //在一个值左右变化，防止左右摆动幅度大
                                                                                                                                                                            //ad_Turn_PWMOUT_TOTAL = duoji_center+(80)*midpoint_error;
        else if (midpoint_error >= 0)                                                                                                                                       //zuo
            ad_Turn_PWMOUT_TOTAL = duoji_center + (ad_Turn_P_L * midpoint_error * midpoint_error + 10) * midpoint_error + ad_Turn_D_L * (midpoint_error - lastpoint_error);
        lastpoint_error = midpoint_error; //记录上次误差

        if (ad_Turn_PWMOUT_TOTAL < duoji_center - 850) //输出限幅
            ad_Turn_PWMOUT_TOTAL = duoji_center - 850;
        if (ad_Turn_PWMOUT_TOTAL > duoji_center + 850)
            ad_Turn_PWMOUT_TOTAL = duoji_center + 850;

        ad_fDirectionControlOut = (int32)ad_Turn_PWMOUT_TOTAL;

        ftm_pwm_duty(FTM1, FTM_CH0, ad_fDirectionControlOut);
        speed_djout = ad_fDirectionControlOut;
    }
}
