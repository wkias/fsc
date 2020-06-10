#ifndef __ADGET_H__
#define __ADGET_H__

#include "common.h"
#include "include.h"

extern int adc_val[6];
extern int adc_errors[3][3];

extern uint16 delayms(uint32 ms);

void adcs_init();
void adc_sampling();
#endif