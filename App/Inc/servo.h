#include "include.h"

extern float64_t servo_out;
extern float64_t ratio;
extern float64_t servo_correct;
extern float servo_errors[3];
extern float servo_pid_param[3];
extern float servo_errors_wight[3];

void servo();
