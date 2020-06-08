#include "common.h"
#include "include.h"


int AD_val_1 = 0;
int AD_val_2 = 0;
int AD_val_3 = 0;
int AD_val_4 = 0;
int AD_val_5 = 0;
int AD_val_6 = 0;

u32 ad_sum = 0;

float ad_fDirectionError[3];
int16 ad_fD[3];

void AD_Init()
{
  adc_init(ADC1_SE4a); //PTE0   左电磁
  adc_init(ADC1_SE5a); //PTE1   最左电磁
  adc_init(ADC1_SE6a); //PTE2  右电磁
  adc_init(ADC1_SE7a); //PTE3  最右电磁
  adc_init(ADC0_SE17); //PTE24  左竖电磁
  adc_init(ADC0_SE18); //PTE25  右竖电磁
}


void ad_sampling()
{
  unsigned int i;

  led(LED1, LED_OFF);
  for (i = 0; i < 50; i++) //Left-Min
  {
    ad_sum += adc_once(ADC1_SE4a, ADC_10bit);
  }
  AD_val_1 = ad_sum / 50;
  ad_sum = 0;

  for (i = 0; i < 50; i++) //Left-max-Min
  {
    ad_sum += adc_once(ADC1_SE5a, ADC_10bit);
  }
  AD_val_1 = ad_sum / 50;
  ad_sum = 0;

  for (i = 0; i < 50; i++) //Right-Min
  {
    ad_sum += adc_once(ADC1_SE6a, ADC_10bit);
  }
  AD_val_3 = ad_sum / 50;
  ad_sum = 0;

  for (i = 0; i < 50; i++) //Right-max-Min
  {
    ad_sum += adc_once(ADC1_SE7a, ADC_10bit);
  }
  AD_val_4 = ad_sum / 50;
  ad_sum = 0;

  for (i = 0; i < 50; i++) //左竖
  {
    ad_sum += adc_once(ADC0_SE17, ADC_10bit);;
  }
  AD_val_5 = ad_sum / 50;
  ad_sum = 0;

  for (i = 0; i < 50; i++) //右竖
  {
    ad_sum += adc_once(ADC0_SE18, ADC_10bit);;
  }
  AD_val_6 = ad_sum / 50;
  ad_sum = 0;

  //显示电压最小值
  LCD_P6x8Str(0, 0, "LMax:      LMin:");
  LCD_P6x8Str(0, 1, "RMax:      RMin:");

  Dis_num(96, 1, AD_val_3); //right
  Dis_num(32, 0, AD_val_2); //left
  Dis_num(96, 0, AD_val_1); //left
  Dis_num(32, 1, AD_val_4); //right
  Dis_num(32, 2, AD_val_5); //left
  Dis_num(96, 2, AD_val_6); //right

  ad_fDirectionError[0] = (float)(AD_val_3 - AD_val_1) / (AD_val_3 + AD_val_1); //水平电感的差比和作为偏差 最边上的2个
                                                                                                //ad_fDirectionError[0] = (ad_fDirectionError[0]>= 1? 1:ad_fDirectionError[0]);	//偏差限幅
  ad_fDirectionError[1] = (float)(AD_val_4 - AD_val_2) / (AD_val_4 + AD_val_2);

  ad_fD[2] = ad_fDirectionError[0] * 20; //40,25,36
  ad_fD[3] = ad_fDirectionError[1] * 20;

  servo();
  carport();

  Dis_num(150, 4, bin_youhuandaoflag);
  Dis_num(150, 6, bin_zuohuandaoflag);
}

void PIT3_IRQHandler(void)
{
  gpio_init(PTB22, GPO, 1);
  sin_youhuandaoflag = 0;
  sin_zuohuandaoflag = 0;
  bin_zuohuandaoflag = 0;
  bin_youhuandaoflag = 0;
  PIT_Flag_Clear(PIT3);
}
