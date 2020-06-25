#ifndef __ADGET_H__
#define __ADGET_H__

#include "common.h"
#include "include.h"

extern uint8 LOST_IN_FRANXX;
extern float32_t adc_val[3][6];
extern float32_t adc_bias[3][3];
extern float32_t adc_bias_gradient[3];

float32_t carmack_sqrt(float32_t x);
void adcs_init();
void adc_sampling();
#endif
