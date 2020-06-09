/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *     
 *    
 *    
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��ʦ����ѧ���У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��ʦ����ѧ
 * @author     ����ͷһ��   �������ɶ�
 * @version     V2.4
 * @date       2018-06-25
 */

#include "common.h"
#include "include.h"

void PIT1_IRQHandler(void);
void PIT2_IRQHandler(void);

void changeinit1();
void changeinit2();
void changeinit3();

void main(void)
{
  LCD_Init();
  led_init(LED0);
  led_init(LED1);
  led_init(LED2);
  led_init(LED3);
  led(LED1, LED_ON);
  led(LED2, LED_ON);
  //����
  pit_init_ms(PIT1, 5);//PIT1��5ms
  set_vector_handler(PIT1_VECTORn, PIT1_IRQHandler);
  enable_irq(PIT1_IRQn);

  //speed_pid
  pit_init_ms(PIT2, 10);                             //��ʼ��PIT2����ʱʱ��Ϊ�� 30ms
  set_vector_handler(PIT2_VECTORn, PIT2_IRQHandler); //����PIT2���жϷ�����Ϊ PIT2_IRQHandler
  enable_irq(PIT2_IRQn);                             //ʹ��PIT2�ж�

  //����͵����ʼ��
  ftm_pwm_init(FTM1, FTM_CH0, 300, 4800); //PTA8���
  ftm_pwm_init(FTM0, FTM_CH2, 10000, 0);  //��ת PTA5 ���
  ftm_pwm_init(FTM0, FTM_CH3, 10000, 0);  //��ת PTA6 ���
  led(LED2, LED_OFF);
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
    changeinit2();
    LCD_P6x8Str(20, 3, "init2");
  }
  if (gpio_get(PTC1) == 1)
  {
    changeinit1();
    LCD_P6x8Str(20, 3, "init1");
  }
  if (gpio_get(PTC4) == 1)
  {
    changeinit3();
    LCD_P6x8Str(20, 3, "init3");
  }

  AD_Init();
  while (1)
  {
    gpio_init(PTB22, GPO, 0);
    ad_sampling();
    servo();
    carport();
  }
}

void changeinit1()
{
  zhidao1 = 900;
  zhidao2 = 875;
  wangdao1 = 850;
  wangdao2 = 825;

  angle1 = 4950 + 850;
  angle2 = 4950 - 770;
  angle3 = 4950 - 480;
  angle4 = 4950 - 480;
  angle5 = 4950 + 500;

  time1 = 210;
  time2 = 290;
  time3 = 140;
  time4 = 140;
  time5 = 200;
}

void changeinit2()
{
  zhidao1 = 1350;
  zhidao2 = 1000;
  wangdao1 = 900;
  wangdao2 = 850;

  angle1 = 4950 + 850;
  angle2 = 4950 - 800;
  angle3 = 4950 - 450;
  angle4 = 4950 - 450;
  angle5 = 4950 + 600;

  time1 = 180;
  time2 = 290;
  time3 = 130;
  time4 = 130;
  time5 = 200;
}

void changeinit3()
{
  zhidao1 = 1800;
  zhidao2 = 1500;
  wangdao1 = 1000;
  wangdao2 = 900;

  angle1 = 4950 + 850;
  angle2 = 4950 - 750;
  angle3 = 4950 - 200;
  angle4 = 4950 - 440;
  angle5 = 4950 + 600;

  time1 = 140;
  time2 = 300;
  time3 = 130;
  time4 = 130;
  time5 = 260;
}
