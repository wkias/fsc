
#include "common.h"
#include "include.h"

void PIT1_IRQHandler(void);
void PIT2_IRQHandler(void);

void config1();
void config2();
void config3();

void main(void)
{
  LCD_init();
  led_init(LED0);
  led_init(LED1);
  led_init(LED2);
  led_init(LED3);

  //���ٶ�ʱ��
  pit_init_ms(PIT1, 5);//PIT1��5ms
  set_vector_handler(PIT1_VECTORn, PIT1_IRQHandler);
  enable_irq(PIT1_IRQn);

  //���ٶ�ʱ��
  pit_init_ms(PIT2, 10);
  set_vector_handler(PIT2_VECTORn, PIT2_IRQHandler);
  enable_irq(PIT2_IRQn);

  //����͵����ʼ��
  ftm_pwm_init(FTM1, FTM_CH0, 300, 4800); //PTA8���
  ftm_pwm_init(FTM0, FTM_CH2, 10000, 0);  //��ת PTA5 ���
  ftm_pwm_init(FTM0, FTM_CH3, 10000, 0);  //��ת PTA6 ���
  
  //���뿪�ؽӿ�
  gpio_init(PTC1, GPI, 0);
  gpio_init(PTC2, GPI, 0);
  gpio_init(PTC3, GPI, 0);
  gpio_init(PTC4, GPI, 0);

  //����ģ���ʼ�����������롢LPTMR_�������
  ftm_quad_init(FTM2); //A10��A11

  //���ڳ�ʼ��
  uart_init(UART4, 115200);

  //�ٶ�ѡ��
  if (gpio_get(PTC2) == 1)
  {
    config2();
    LCD_P6x8Str(20, 3, "init2");
  }
  if (gpio_get(PTC1) == 1)
  {
    config1();
    LCD_P6x8Str(20, 3, "init1");
  }
  if (gpio_get(PTC4) == 1)
  {
    config3();
    LCD_P6x8Str(20, 3, "init3");
  }

  adcs_init();
  while (1)
  {
    gpio_init(PTB22, GPO, 0);
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
