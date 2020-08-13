#include "include.h"

int16 ftm_quad_values[3] = {0};
float32_t filter_wight[3] = {ENCODER_FILTER_WIGHT_0,
                             ENCODER_FILTER_WIGHT_1,
                             ENCODER_FILTER_WIGHT_2};
int16 motor_pulse = 0; // 电机观测速度

int8 motor_protection_switcher = 0; // 电机保护拨码开关标记
int8 motor_out_of_order = 0;        // 电机故障标记
// PID参数，可在settings.h中更改，构建数组可动态调参
float32_t motor_pid_param[3] = {MOTOR_PID_PARAMETER_P,
                                MOTOR_PID_PARAMETER_I,
                                MOTOR_PID_PARAMETER_D};
float32_t expected_motor_out = 0;                        // 期望速度
float32_t motor_errors[3];                               // 本次速度偏差，上次偏差，前次偏差
float32_t motor_out[2] = {MOTOR_VELOCITY_BASE_POINT, 0}; // 输出速度
float32_t motor_velocity_sup = MOTOR_VELOCITY_SUPERIOR_LIMIT;
float32_t motor_velocity_base = MOTOR_VELOCITY_BASE_POINT;

// 编码器测速
void encoder(void)
{
  PIT_Flag_Clear(PIT1); // 清中断标志位

  for (int8 i = 1; i > -1; i--)
  {
    ftm_quad_values[i + 1] = ftm_quad_values[i];
  }
  ftm_quad_values[0] = ftm_quad_get(PORT_ENCODER);
  ftm_quad_clean(PORT_ENCODER);

  // 负值处理
  ftm_quad_values[0] = (ftm_quad_values[0] > 0) ? ftm_quad_values[0] : -ftm_quad_values[0];

  // 权值滤波
  motor_pulse = (int16)(ftm_quad_values[0] * filter_wight[0] +
                        ftm_quad_values[1] * filter_wight[1] +
                        ftm_quad_values[2] * filter_wight[2]);
  motor_pulse *= 15;
}

// 电机调速
void motor()
{
  PIT_Flag_Clear(PIT2);

// ⚠电机保护
#ifdef MOTOR_PROTECTION
  if (!motor_pulse && motor_out[0] && motor_protection_switcher)
  {
    disable_irq(PIT2_IRQn); // 不再定时调
    motor_out_of_order = 1;
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);
    return;
  }
#endif

  // 速度误差
  motor_errors[0] = expected_motor_out - motor_pulse;
  // 增量PID，速度误差修正
  motor_out[0] += motor_pid_param[0] * (motor_errors[0] - motor_errors[1]) +
                  motor_pid_param[1] * motor_errors[0] +
                  motor_pid_param[2] * (motor_errors[0] - 2 * motor_errors[1] + motor_errors[2]);

  //  限速输出
  if (motor_out[0] >= 0)
  {
    motor_out[0] = ((motor_out[0] > motor_velocity_sup) ? motor_velocity_sup : motor_out[0]);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, (int)motor_out[0]);
  }
  else
  {
    motor_out[0] = ((motor_out[0] < -motor_velocity_sup) ? -motor_velocity_sup : motor_out[0]);
    ftm_pwm_duty(PORT_MOTOR, FTM_CH2, 0);
  }

  motor_out[1] = motor_out[0];
  motor_errors[2] = motor_errors[1];
  motor_errors[1] = motor_errors[0];
}
