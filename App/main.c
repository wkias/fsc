#include "include.h"

void print()
{
  PIT_Flag_Clear(PIT0);

  for (int i = 0; i < 6; i++)
  {
    Dis_num(COLUMN_1, i, adc_val[0][i]);
  }

  Dis_num(COLUMN_2, 0, adc_bias[0][0]);
  Dis_num(COLUMN_2, 1, adc_bias[0][1]);
  Dis_num(COLUMN_2, 2, adc_bias[0][2]);
  Dis_num(COLUMN_2, 3, adc_bias_gradient[0]);
  if (LOST_IN_FRANXX)
  {
    LCD_P6x8Str(COLUMN_2, 7, " LIF");
  }
  else
  {
    LCD_P6x8Str(COLUMN_2, 4, "    ");
  }

  Dis_num(COLUMN_3, 0, servo_bias[0]);
  Dis_num(COLUMN_3, 1, servo_correct);
  Dis_num(COLUMN_3, 2, servo_out);
  Dis_num(COLUMN_3, 4, servo_pid_param[0]);
  Dis_num(COLUMN_3, 5, servo_pid_param[2]);
  if (rotary_road == 1)
  {
    LCD_P6x8Str(COLUMN_3, 7, "  R");
  }
  else if (rotary_road == -1)
  {
    LCD_P6x8Str(COLUMN_3, 7, "  L");
  }
  else
  {
    LCD_P6x8Str(COLUMN_3, 7, "   ");
  }

  Dis_num(COLUMN_4, 0, motor_errors[0]);
  Dis_num(COLUMN_4, 1, expected_motor_out);
  Dis_num(COLUMN_4, 2, motor_out[0]);
  Dis_num(COLUMN_4, 3, motor_pulse);
  Dis_num(COLUMN_4, 4, motor_pid_param[0]);
  Dis_num(COLUMN_4, 5, motor_pid_param[1]);
  Dis_num(COLUMN_4, 6, motor_pid_param[2]);

#ifdef UART_BLE
  static int8 buff[20];
  for (int i = 0; i < 6; i++)
  {
    buff[i] = adc_val[0][i];
  }
  buff[6] = adc_bias[0][0];
  buff[7] = adc_bias[0][1];
  buff[8] = adc_bias[0][2];
  buff[9] = servo_bias[0];
  buff[10] = servo_correct;
  buff[11] = servo_out;
  buff[12] = servo_pid_param[0];
  buff[13] = servo_pid_param[2];
  buff[14] = motor_errors[0];
  buff[15] = expected_motor_out;
  buff[16] = motor_out;
  buff[17] = motor_pulse;
  buff[18] = '\0';
  buff[19] = '\n';
  uart_putbuff(VCAN_PORT, buff, sizeof(buff));
#endif
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

  //舵机和电机初始化
  ftm_pwm_init(PORT_SERVO, FTM_CH0, 300, SERVO_BASE_POINT); //PTA8舵机
  ftm_pwm_init(PORT_MOTOR, FTM_CH2, 10000, 0);              //正转 PTA5 电机
  ftm_pwm_init(PORT_MOTOR, FTM_CH3, 10000, 0);              //反转 PTA6 电机

  //测速模块初始化：正交解码、LPTMR_脉冲计数
  ftm_quad_init(PORT_ENCODER);

  //中断优先级
  NVIC_SetPriorityGrouping(4);
  NVIC_SetPriority(PORTA_IRQn, 0);
  NVIC_SetPriority(PIT2_IRQn, 1);
  NVIC_SetPriority(PIT1_IRQn, 2);
  NVIC_SetPriority(PIT0_IRQn, 3);

  //车库检查-中断
  port_init(PORT_REED_SWITCHER, ALT0 | IRQ_FALLING | PULLUP); //GPIO，下降沿触发中断，上拉电阻
  set_vector_handler(PORTD_VECTORn, carport);
  enable_irq(PORTD_IRQn);

  // 打印-定时器中断
  pit_init_ms(PIT0, PRINT_DELAY);
  set_vector_handler(PIT0_VECTORn, print);
  enable_irq(PIT0_IRQn);

  // 测速-定时器中断
  pit_init_ms(PIT1, 5);
  set_vector_handler(PIT1_VECTORn, encoder);
  enable_irq(PIT1_IRQn);

  // 调速-定时器中断
  pit_init_ms(PIT2, 10);
  set_vector_handler(PIT2_VECTORn, motor);
  enable_irq(PIT2_IRQn);

  // pit_init_ms(PIT3, 10000);
  // set_vector_handler(PIT3_VECTORn, clear);
  // disable_irq(PIT3_IRQn);

#ifdef UART_BLE
  //蓝牙模块
  uart_init(VCAN_PORT, VCAN_BAUD);
  set_vector_handler(UART0_RX_TX_VECTORn, dynamic_param);
  uart_rx_irq_en(VCAN_PORT);
  LCD_P6x8Str(COLUMN_2, 7, "BLE");
#endif

#ifdef FLASH_WRITE_PARAM
  //片内闪存
  flash_init();
  gpio_init(PTB22, GPO, 0);
  //flash写参数
  if (0x12345678 != flash_read(SECTOR_NO, 0, FLASH_WRITE_TYPE))
  {
    flash_erase_sector(SECTOR_NO);
    flash_write(SECTOR_NO, 4, 1);
    flash_write(SECTOR_NO, 0, 0x12345678);
    gpio_set(PTB22, 1);
    DELAY_MS(100);
    gpio_set(PTB22, 0);
    DELAY_MS(100);
  }
  uint32 param = flash_read(SECTOR_NO, 4, FLASH_WRITE_TYPE);
  flash_erase_sector(SECTOR_NO);
  flash_write(SECTOR_NO, 4, param + 1);
  flash_write(SECTOR_NO, 0, 0x12345678);
  servo_pid_param[0] = param;
  for (uint8 i = param / 2; i; i--)
  {
    gpio_set(PTB22, 1);
    DELAY_MS(100);
    gpio_set(PTB22, 0);
    DELAY_MS(100);
  }
#endif

#ifdef ENABLE_PARAM_SWITCHER
  param_switcher();
#endif

  adcs_init();

  while (1)
  {
    adc_sampling();
    servo();
  }
}
