#include "include.h"

float64_t adc_val[6] = {0};
float64_t adc_errors[3];
int32 sampling_f = ADC_SAMPLING_FREQ + 2;
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
  for (int8 i = 0; i < 6; i++)
  {
    adc_init(port_adc[i]);
  }
}

void adc_sampling()
{
  static float64_t max = 0;
  static float64_t min = 0;
  static float64_t ad_sum = 0;

  for (int8 i = 0; i < 6; i++)
  {
    max = adc_once(port_adc[i], ADC_SAMPLING_PRECISION);
    min = adc_once(port_adc[i], ADC_SAMPLING_PRECISION);
    for (int8 j = 0; j < sampling_f; j++)
    {
      adc_val[i] = adc_once(port_adc[i], ADC_SAMPLING_PRECISION);
      max = (max > adc_val[i]) ? max : adc_val[i];
      min = (min < adc_val[i]) ? min : adc_val[i];
      ad_sum += adc_val[i];
    }
    ad_sum -= max;
    ad_sum -= min;
    adc_val[i] = ad_sum / ADC_SAMPLING_FREQ / 10;
    ad_sum = 0;
  }

  //水平电感的和比差作为偏差
  adc_errors[0] = (adc_val[0] + adc_val[5]) / (adc_val[0] - adc_val[5]) * 100;
  adc_errors[1] = (adc_val[1] + adc_val[4]) / (adc_val[1] - adc_val[4]) * 100;
  adc_errors[2] = (adc_val[2] + adc_val[3]) / (adc_val[2] - adc_val[3]) * 100;
}
