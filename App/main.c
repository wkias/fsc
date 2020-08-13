#include "include.h"

void print()
{
  PIT_Flag_Clear(PIT0);
  LCD_CLS();

  for (int i = 0; i < 6; i++)
  {
    Dis_num(COLUMN_1, i, adc_val[0][i]);
  }
  LCD_P6x8Str(COLUMN_1, 7, switch_ch);

  Dis_num(COLUMN_2, 0, adc_bias[0][0]);
  Dis_num(COLUMN_2, 1, adc_bias[0][1]);
  Dis_num(COLUMN_2, 2, adc_bias[0][2]);
  if (LOST_IN_FRANXX)
  {
    LCD_P6x8Str(COLUMN_2, 7, " LIF"); // 丢线 LOST IN FRANXX
  }

  Dis_num(COLUMN_3, 0, servo_bias[0]);
  Dis_num(COLUMN_3, 1, servo_correct);
  Dis_num(COLUMN_3, 2, servo_out);
  Dis_num(COLUMN_3, 4, servo_pid_param[0]);
  Dis_num(COLUMN_3, 5, servo_pid_param[2]);
  if (rotary_road == 1)
  {
    LCD_P6x8Str(COLUMN_3, 7, "  R"); // 右环
  }
  else if (rotary_road == -1)
  {
    LCD_P6x8Str(COLUMN_3, 7, "  L"); // 左环
  }

  Dis_num(COLUMN_4, 0, motor_errors[0]);
  Dis_num(COLUMN_4, 1, expected_motor_out);
  Dis_num(COLUMN_4, 2, motor_out[0]);
  Dis_num(COLUMN_4, 3, motor_pulse);
  if (motor_out_of_order)
  {
    LCD_P6x8Str(COLUMN_4, 7, " MOOO");
  }
}

void main(void)
{
  // 屏幕
  LCD_Init();

  // LED
  led_init(LED0);
  led_init(LED1);
  led_init(LED2);
  led_init(LED3);

  // 蜂鸣器
  gpio_init(PORT_BEEPER, GPO, 0);

  // 舵机和电机初始化
  ftm_pwm_init(PORT_SERVO, FTM_CH0, 50, SERVO_BASE_POINT); // PTA8 舵机
  ftm_pwm_init(PORT_MOTOR, FTM_CH2, 13000, 0);             // 正转 PTA5 电机
  ftm_pwm_init(PORT_MOTOR, FTM_CH3, 13000, 0);             // 反转 PTA6 电机

  // 测速模块初始化：正交解码、LPTMR脉冲计数
  ftm_quad_init(PORT_ENCODER);

  // 中断优先级
  NVIC_SetPriorityGrouping(4);
  NVIC_SetPriority(PORTA_IRQn, 0);
  NVIC_SetPriority(PIT2_IRQn, 1);
  NVIC_SetPriority(PIT1_IRQn, 2);
  NVIC_SetPriority(PIT0_IRQn, 3);

  port_init(PORT_REED_SWITCHER, PULLDOWN);
  gpio_init(PORT_REED_SWITCHER, GPO, 0);

  // 光电开关
  port_init(PORT_LIGHT_SWITCHER, PULLUP);
  gpio_init(PORT_LIGHT_SWITCHER, GPO, 1);

  // 打印-定时器中断
  pit_init_ms(PIT0, PRINT_DELAY);
  set_vector_handler(PIT0_VECTORn, print);
  enable_irq(PIT0_IRQn);

  go_out();

  // 测速-定时器中断
  pit_init_ms(PIT1, 5);
  set_vector_handler(PIT1_VECTORn, encoder);
  enable_irq(PIT1_IRQn);

  // 调速-定时器中断
  pit_init_ms(PIT2, 10);
  set_vector_handler(PIT2_VECTORn, motor);
  enable_irq(PIT2_IRQn);

  param_switcher();
  adcs_init();
  motor_protection_switcher = 1;

  while (1)
  {
    if (light_switcher && gpio_get(PORT_LIGHT_SWITCHER) == 0)
    {
      rampway();
    }
    adc_sampling();
    servo();
  }
}
