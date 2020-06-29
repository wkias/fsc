#include "include.h"

extern float32_t ftm_quad_values[3];
extern float32_t filter_wight[3];
extern uint16 motor_pulse;

extern float32_t motor_pid_param[3];
extern float32_t expected_motor_out;
extern float32_t motor_errors[3];
extern float32_t motor_out[2];

void encoder();
void motor();
void decelerate();
