#include "include.h"

extern int line_speed;
extern uint16 expected_motor_out;
extern uint16 motor_pulse;

void PIT1_IRQHandler();
void PIT2_IRQHandler();
