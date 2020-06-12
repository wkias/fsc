#ifndef __ADGET_H__
#define __ADGET_H__

#include "common.h"
#include "include.h"

extern float32_t adc_val[6];
extern float32_t adc_bias[3];

void adcs_init();
void adc_sampling();
#endif