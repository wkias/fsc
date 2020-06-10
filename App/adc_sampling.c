#include "include.h"

int adc_val[6] = {0};
int adc_errors[3][3]; //三行三列矩阵
ADCn_Ch_e port_adc[6] = {
    ADC0_SE17, //PTE24   1
    ADC1_SE5a, //PTE1    2
    ADC1_SE4a, //PTE0    3
    ADC1_SE6a, //PTE2    4
    ADC1_SE7a, //PTE3    5
    ADC0_SE18  //PTE25   6
};

void adcs_init()
{
  for (int i = 0; i < 6; i++)
  {
    adc_init(port_adc[i]);
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
    max = adc_once(port_adc[i], ADC_SAMPLING_PRECISION);
    min = adc_once(port_adc[i], ADC_SAMPLING_PRECISION);
    for (int j = 0; j < sampling_f; j++)
    {
      adc_val[i] = adc_once(port_adc[i], ADC_SAMPLING_PRECISION);
      max = (max > adc_val[i]) ? max : adc_val[i];
      min = (min < adc_val[i]) ? min : adc_val[i];
      ad_sum += adc_val[i];
    }
    ad_sum -= max;
    ad_sum -= min;
    adc_val[i] = ad_sum / 48;
    ad_sum = 0;
    Dis_num(COLUMN_1, i, adc_val[i]);
  }

  for (int i = 2; i > -1; i--)
  {
    for (int j = 0; j < 2; j++)
    {
      adc_errors[i][j] = adc_errors[i - 1][j];
    }
  }
  //水平电感的差比和作为偏差
  adc_errors[0][0] = (adc_val[0] - adc_val[5]) / (adc_val[0] + adc_val[5]) * 20;
  adc_errors[0][1] = (adc_val[1] - adc_val[4]) / (adc_val[1] + adc_val[4]) * 20;
  adc_errors[0][2] = (adc_val[2] - adc_val[3]) / (adc_val[2] + adc_val[3]) * 20;
}
