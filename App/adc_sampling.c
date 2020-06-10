#include "include.h"

double adc_val[6] = {0};
double adc_errors[3];
int sampling_f = ADC_SAMPLING_FREQ + 2;
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
  double max = 0;
  double min = 0;
  double ad_sum = 0;

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
    adc_val[i] = (float)ad_sum / ADC_SAMPLING_FREQ / 10;
    ad_sum = 0;
  }

  //ˮƽ��еĺͱȲ���Ϊƫ��
  adc_errors[0] = (adc_val[0] + adc_val[5]) / (adc_val[0] - adc_val[5]);
  adc_errors[1] = (adc_val[1] + adc_val[4]) / (adc_val[1] - adc_val[4]);
  adc_errors[2] = (adc_val[2] + adc_val[3]) / (adc_val[2] - adc_val[3]);
}
