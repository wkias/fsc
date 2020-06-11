#include "include.h"

extern float32_t servo_pid_param[3];
extern float32_t servo_errors_wight[3];
extern float64_t servo_errors[3];
extern float64_t servo_correct;
extern float64_t servo_out;
extern float32_t ratio;

void servo();
