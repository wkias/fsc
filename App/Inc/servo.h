#include "include.h"

extern double servo_out;
extern double ratio;
extern double servo_correct;
extern double servo_errors[3];
extern float servo_pid_param[3];
extern float servo_errors_wight[3];

void servo();
