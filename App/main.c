#include "include.h"

void config1();
void config2();
void config3();

void main(void)
{
  //��Ļ
  LCD_init();

  //���뿪�ؽӿ�
  gpio_init(PORT_SWITCHER_1, GPI, 0);
  gpio_init(PORT_SWITCHER_2, GPI, 0);
  gpio_init(PORT_SWITCHER_3, GPI, 0);
  gpio_init(PORT_SWITCHER_4, GPI, 0);

  //����͵����ʼ��
  ftm_pwm_init(PORT_SERVO, FTM_CH0, 300, 4800); //PTA8���
  ftm_pwm_init(PORT_MOTOR, FTM_CH2, 10000, 0);  //��ת PTA5 ���
  ftm_pwm_init(PORT_MOTOR, FTM_CH3, 10000, 0);  //��ת PTA6 ���

  //����ģ���ʼ�����������롢LPTMR_�������
  ftm_quad_init(PORT_CODER); //A10��A11

  //������
  set_vector_handler(PORTA_VECTORn, carport);
  enable_irq(PORTA_VECTORn);

  //���ٶ�ʱ��
  pit_init_ms(PIT1, 5);
  set_vector_handler(PIT1_VECTORn, PIT1_IRQHandler);
  enable_irq(PIT1_IRQn);

  //���ٶ�ʱ��
  pit_init_ms(PIT2, 10);
  set_vector_handler(PIT2_VECTORn, motor);
  enable_irq(PIT2_IRQn);

  //���ڳ�ʼ��
  uart_init(UART4, 115200);

  //�ٶ�ѡ��
  if (gpio_get(PORT_SWITCHER_1) == 1)
  {
    config1();
    LCD_P6x8Str(20, 3, "init1");
  }
  if (gpio_get(PORT_SWITCHER_2) == 1)
  {
    config2();
    LCD_P6x8Str(20, 3, "init2");
  }
  if (gpio_get(PORT_SWITCHER_3) == 1)
  {
    config3();
    LCD_P6x8Str(20, 3, "init3");
  }

  adcs_init();
  while (1)
  {
    adc_sampling();
    servo();
    carport();
  }
}

void config1()
{
  zhidao1 = 900;
  zhidao2 = 875;
  wangdao1 = 850;
  wangdao2 = 825;
}

void config2()
{
  zhidao1 = 1350;
  zhidao2 = 1000;
  wangdao1 = 900;
  wangdao2 = 850;
}

void config3()
{
  zhidao1 = 1800;
  zhidao2 = 1500;
  wangdao1 = 1000;
  wangdao2 = 900;
}
