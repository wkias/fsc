#include "include.h"

int adc_val[6] = {0};
int adc_errors[3];

ADCn_Ch_e adc[6] = {
    ADC1_SE4a, //PTE0   左电磁
    ADC1_SE5a, //PTE1   最左电磁
    ADC1_SE6a, //PTE2  右电磁
    ADC1_SE7a, //PTE3  最右电磁
    ADC0_SE17, //PTE24  左竖电磁
    ADC0_SE18  //PTE25  右竖电磁
};

void adcs_init()
{
  for (int i = 0; i < 6; i++)
  {
    adc_init(adc[i]);
  }
}

void adc_sampling()
{
  int max = 0;
  int min = 0;
  int ad_sum = 0;
  static int sampling_f = ADC_SAMPLING_FREQ;

  for (int i = 0; i < 6; i++)
  {
    max = adc_once(adc[i], ADC_10bit);
    min = adc_once(adc[i], ADC_10bit);
    for (int j = 0; j < sampling_f; j++)
    {
      adc_val[i] = adc_once(adc[i], ADC_10bit);
      if (adc_val[i] > max)
      {
        max = adc_val[i];
      }
      if (adc_val[i] < min)
      {
        min = adc_val[i];
      }
      ad_sum += adc_val[i];
    }
    ad_sum -= max;
    ad_sum -= min;
    adc_val[i] = ad_sum / 48;
    ad_sum = 0;
  }

  Dis_num(96, 1, adc_val[2]); //right
  Dis_num(32, 0, adc_val[1]); //left
  Dis_num(96, 0, adc_val[0]); //left
  Dis_num(32, 1, adc_val[3]); //right
  Dis_num(32, 2, adc_val[4]); //left
  Dis_num(96, 2, adc_val[5]); //right

  //水平电感的差比和作为偏差 最边上的2个
  adc_errors[1] = (adc_val[2] - adc_val[0]) / (adc_val[2] + adc_val[0]) * 20;
  adc_errors[2] = (adc_val[3] - adc_val[1]) / (adc_val[3] + adc_val[1]) * 20;

}
