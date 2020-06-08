#ifndef __ADGET_H__
#define __ADGET_H__ 


#include "common.h"
#include "include.h"
extern int AD_val_1;
extern int AD_val_2;
extern int AD_val_3;
extern int AD_val_4;
extern int AD_val_5;
extern int AD_val_6;

extern int16 ad_fD[3];

extern uint16 delayms(uint32  ms);

void AD_Init();
void ad_sampling();
#endif