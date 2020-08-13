#include "include.h"

float32_t adc_val[3][6] = {0};  //  ���ֵ
float32_t adc_bias[3][3] = {0}; //  ���ƫ��
int32 sampling_f = ADC_SAMPLING_FREQ + 2;
ADCn_Ch_e port_adc[6] = {
    ADC0_SE17, // PTE24   1
    ADC0_SE18, // PTE25   6
    ADC1_SE7a, // PTE3    5
    ADC1_SE6a, // PTE2    4
    ADC1_SE5a, // PTE1    2
    ADC1_SE4a, // PTE0    3
};

void adcs_init()
{
  for (int8 i = 0; i < 6; i++)
  {
    adc_init(port_adc[i]);
  }
}

// ��в���
void adc_sampling()
{
  static float32_t ad_sum = 0;
  static float32_t adc_val_tmp[ADC_SAMPLING_FREQ] = {0};

  // ����ʱ������
  for (int8 i = 0; i < 2; i++)
  {
    for (int8 j = 0; j < 5; j++)
    {
      adc_val[i + 1][j] = adc_val[i][j];
    }
    for (int8 j = 0; j < 2; j++)
    {
      adc_bias[i + 1][j] = adc_bias[i][j];
    }
  }

  // ���� ��ֵ�˲�
  for (int8 i = 0; i < 6; i++)
  {
    ad_sum = 0;
    for (int8 j = 0; j < ADC_SAMPLING_FREQ; j++)
    {
      adc_val_tmp[j] = adc_once(port_adc[i], ADC_SAMPLING_PRECISION);
      ad_sum += adc_val_tmp[j];
    }
    // ������
    heap_sort(adc_val_tmp, ADC_SAMPLING_FREQ);
    // ���ֵ
    for (int8 j = 0; j < ADC_SAMPLING_DEPRICATE / 2; j++)
    {
      ad_sum -= adc_val_tmp[j];
      ad_sum -= adc_val_tmp[ADC_SAMPLING_FREQ - j - 1];
    }
    adc_val[0][i] = ad_sum / (ADC_SAMPLING_FREQ - ADC_SAMPLING_DEPRICATE);
  }

  // ����ƫ��-��Ⱥ�-�����������Ÿ�Ӧǿ����ƫ��ģ�N�ͣ��߽׺�������������һ�����������ĳƿ�����Ÿ�Ӧǿ����ƫ���Sigmoid����
  adc_bias[0][0] = (carmack_sqrt(adc_val[0][5]) - carmack_sqrt(adc_val[0][0])) / (adc_val[0][5] + adc_val[0][0]) * 2000; // ��ֱ���
  adc_bias[0][1] = (carmack_sqrt(adc_val[0][4]) - carmack_sqrt(adc_val[0][1])) / (adc_val[0][4] + adc_val[0][1]) * 2000; // ˮƽ���-��Ե
  adc_bias[0][2] = (carmack_sqrt(adc_val[0][3]) - carmack_sqrt(adc_val[0][2])) / (adc_val[0][3] + adc_val[0][2]) * 2000; // ˮƽ���-�м�
}

// ƽ����
float32_t carmack_sqrt(float32_t x)
{
  float32_t xhalf = 0.5f * x;
  int32 i = *(int32 *)&x;         // get bits for floating VALUE
  i = 0x5f3759df - (i >> 1);      // gives initial guess y0
  x = *(float32_t *)&i;           // convert bits BACK to float
  x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
  x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
  x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
  return (1 / x);
}
