#include "include.h"

void print()
{
  Dis_num(COLUMN_2, 0, adc_errors[0][0]);
  Dis_num(COLUMN_2, 1, adc_errors[0][1]);
  Dis_num(COLUMN_2, 2, adc_errors[0][2]);

  Dis_num(COLUMN_3, 0, servo_errors[0]);
  Dis_num(COLUMN_3, 1, servo_correct);
  Dis_num(COLUMN_3, 2, servo_out);

  Dis_num(COLUMN_4, 0, motor_errors[0]);
  Dis_num(COLUMN_4, 1, expected_motor_out);
  Dis_num(COLUMN_4, 2, motor_out);
  Dis_num(COLUMN_4, 3, motor_pulse);
}

void main(void)
{
  //屏幕
  LCD_Init();

  //LED
  led_init(LED0);
  led_init(LED1);
  led_init(LED2);
  led_init(LED3);

  //播码开关接口
  gpio_init(PORT_SWITCHER_1, GPI, 0);
  gpio_init(PORT_SWITCHER_2, GPI, 0);
  gpio_init(PORT_SWITCHER_3, GPI, 0);
  gpio_init(PORT_SWITCHER_4, GPI, 0);

  //舵机和电机初始化
  ftm_pwm_init(PORT_SERVO, FTM_CH0, 300, SERVO_BASE_POINT); //PTA8舵机
  ftm_pwm_init(PORT_MOTOR, FTM_CH2, 10000, 0);              //正转 PTA5 电机
  ftm_pwm_init(PORT_MOTOR, FTM_CH3, 10000, 0);              //反转 PTA6 电机

  //测速模块初始化：正交解码、LPTMR_脉冲计数
  ftm_quad_init(PORT_CODER); //A10和A11

  //车库检查
  set_vector_handler(PORTA_VECTORn, carport);
  enable_irq(PORTA_VECTORn);

  // 测速定时器
  pit_init_ms(PIT1, 5);
  set_vector_handler(PIT1_VECTORn, coder);
  enable_irq(PIT1_IRQn);

  // 调速定时器
  pit_init_ms(PIT2, 10);
  set_vector_handler(PIT2_VECTORn, motor);
  enable_irq(PIT2_IRQn);

  //串口初始化
  // uart_init(UART4, 115200);

#if ENABLE_PARAM_SWITCHER
  param_switcher();
#endif

  adcs_init();
  while (1)
  {
#if ENABLE_LED
    led(LED_CARPORT, LED_ON);
#endif
    carport();
#if ENABLE_LED

    led(LED_CARPORT, LED_OFF);
    led(LED_SAMPLING, LED_ON);
#endif
    adc_sampling();
#if ENABLE_LED
    led(LED_SAMPLING, LED_OFF);
    led(LED_SERVO, LED_ON);
#endif
    servo();
#if ENABLE_LED

    led(LED_SERVO, LED_OFF);
    led(LED_MOTOR, LED_ON);
    // coder();
    // motor();
    led(LED_MOTOR, LED_OFF);
#endif
    print();
  }
}
