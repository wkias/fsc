#ifndef __ADGET_H__
#define __ADGET_H__

#include "common.h"
#include "include.h"

extern double adc_val[6];
extern double adc_errors[3];

void adcs_init();
void adc_sampling();
#endif