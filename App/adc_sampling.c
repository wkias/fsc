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

  //采样均值滤波
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
    ad_sum = 0;
  }

#ifdef INDUCTOR_CENTER_DISTANCE
  //计算电感和中线的距离-mm
  for (int8 i = 0; i < 6; i++)
  {
    //电感值和中线偏差非线性关系，差比和作偏差不稳定
    adc_val[i] = solve(adc_val[i]) * 100;
  }

  //中线偏差-mm
  adc_bias[0] = (adc_val[5] - adc_val[0]) / 2; //垂直电感
  adc_bias[1] = (adc_val[4] - adc_val[1]) / 2; //水平电感-边缘
  adc_bias[2] = (adc_val[3] - adc_val[2]) / 2; //水平电感-中间
#else
  //中线偏差-无量纲量
  adc_bias[0] = (adc_val[5] - adc_val[0]) / (adc_val[5] + adc_val[0]) * 100; //垂直电感
  adc_bias[1] = (adc_val[4] - adc_val[1]) / (adc_val[4] + adc_val[1]) * 100; //水平电感-边缘
  adc_bias[2] = (adc_val[3] - adc_val[2]) / (adc_val[3] + adc_val[2]) * 100; //水平电感-中间
#endif
}

#ifdef INDUCTOR_CENTER_DISTANCE
//解三次函数实根
float32_t solve(float32_t adc_val)
{
  return adc_height * adc_height / sqrt_3(-27 * adc_val / (2 * adc_slope) + sqrt_(729 * adc_val * adc_val / adc_slope / adc_slope + 108 * adc_height * adc_height * adc_height * adc_height * adc_height * adc_height) / 2) -
         sqrt_3(-27 * adc_val / (2 * adc_slope) + sqrt_(729 * adc_val * adc_val / adc_slope / adc_slope + 108 * adc_height * adc_height * adc_height * adc_height * adc_height * adc_height) / 2) / 3;
}

//解平方根
float32_t sqrt_(float32_t x)
{
  float32_t y;
  arm_sqrt_f32(x, &y);
  return y;
}

//牛顿迭代求三次方根近似值，解范围[-10000,10000]
float32_t sqrt_3(float32_t x)
{
  float64_t l = -10000, r = 10000, mid;
  //浮点数二分
  while (r - l > 1e-7)
  {
    mid = (l + r) / 2;
    if ((mid * mid * mid) >= x)
      r = mid;
    else
      l = mid;
  }
  return l;
}
#endif
