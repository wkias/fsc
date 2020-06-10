#include "include.h"

extern int16 ftm_quad_values[3];
extern int16 filter_wight[3];
extern uint16 motor_pulse;
extern uint16 expected_motor_out;
extern uint32 motor_out;
extern int32 motor_errors[3];
extern float motor_param[3];

void encoder();
void motor();
