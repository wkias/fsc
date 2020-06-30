#include "common.h"
#include "include.h"

extern float32_t adc_val[3][6];
extern float32_t adc_bias[3][3];

float32_t carmack_sqrt(float32_t x);
void adcs_init();
void adc_sampling();
