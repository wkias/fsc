#include "include.h"

float32_t adc_val[6] = {0};
float32_t adc_bias[3];
float32_t adc_slope = ADC_SAMPLING_PARAMETER_SLOPE;
float32_t adc_height = ADC_SAMPLING_PARAMETER_HEIGHT;
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
  static float32_t max = 0;
  static float32_t min = 0;
  static float32_t ad_sum = 0;

  //������ֵ�˲�
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
    adc_val[i] = ad_sum / ADC_SAMPLING_FREQ;
    adc_val[i] = (adc_val[i] - min) / (max - min) * 100; //��һ��
    ad_sum = 0;
  }

  //�����к����ߵľ���-cm
  for (int8 i = 0; i < 6; i++)
  {
    //���ֵ������ƫ������Թ�ϵ����Ⱥ���ƫ��ȶ�
    arm_sqrt_f32((adc_slope * adc_height / adc_val[i]), adc_val + i);
  }

  //����ƫ��-cm
  adc_bias[0] = (adc_val[5] - adc_val[0]) / 2;//��ֱ���
  adc_bias[1] = (adc_val[4] - adc_val[1]) / 2;//ˮƽ���-��Ե
  adc_bias[2] = (adc_val[3] - adc_val[2]) / 2;//ˮƽ���-�м�

}
