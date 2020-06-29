#include "include.h"

extern float32_t servo_pid_param[3];
extern float32_t servo_bias_wight[3];
extern float32_t servo_bias[3];
extern float32_t servo_correct;
extern float32_t servo_out;
extern float32_t ratio;
extern int8 LOST_IN_FRANXX;
extern int8 rotary_road;

void servo();
void clear();
