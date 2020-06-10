#include "include.h"

void main(void)
{
  //��Ļ
  LCD_Init();

  //���뿪�ؽӿ�
  gpio_init(PORT_SWITCHER_1, GPI, 0);
  gpio_init(PORT_SWITCHER_2, GPI, 0);
  gpio_init(PORT_SWITCHER_3, GPI, 0);
  gpio_init(PORT_SWITCHER_4, GPI, 0);

  //����͵����ʼ��
  ftm_pwm_init(PORT_SERVO, FTM_CH0, 300, SERVO_BASE_POINT); //PTA8���
  ftm_pwm_init(PORT_MOTOR, FTM_CH2, 10000, 0);              //��ת PTA5 ���
  ftm_pwm_init(PORT_MOTOR, FTM_CH3, 10000, 0);              //��ת PTA6 ���

  //����ģ���ʼ�����������롢LPTMR_�������
  ftm_quad_init(PORT_CODER); //A10��A11

  //������
  set_vector_handler(PORTA_VECTORn, carport);
  enable_irq(PORTA_VECTORn);

  //���ٶ�ʱ��
  pit_init_ms(PIT1, 5);
  set_vector_handler(PIT1_VECTORn, coder);
  enable_irq(PIT1_IRQn);

  //���ٶ�ʱ��
  pit_init_ms(PIT2, 10);
  set_vector_handler(PIT2_VECTORn, motor);
  enable_irq(PIT2_IRQn);

  //���ڳ�ʼ��
  uart_init(UART4, 115200);

  #if ENABLE_PARAM_SWITCHER
  param_switcher();
  #endif

  adcs_init();
  while (1)
  {
    carport();
    adc_sampling();
    servo();
  }
}
