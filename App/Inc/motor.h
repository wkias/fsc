#include "include.h"

extern int line_speed;
extern uint16 ex_speed;
extern uint16 g_Speedgoal, RightMotorPulse; //目标速度、右电机测速

void PIT1_IRQHandler();
void PIT2_IRQHandler();
