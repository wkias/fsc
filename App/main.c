/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *     
 *    
 *    
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山东师范大学所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山东师范大学
 * @author     摄像头一队   开车开派队
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
  //测速
  pit_init_ms(PIT1, 5);//PIT1，5ms
  set_vector_handler(PIT1_VECTORn, PIT1_IRQHandler);
  enable_irq(PIT1_IRQn);

  //speed_pid
  pit_init_ms(PIT2, 10);                             //初始化PIT2，定时时间为： 30ms
  set_vector_handler(PIT2_VECTORn, PIT2_IRQHandler); //设置PIT2的中断服务函数为 PIT2_IRQHandler
  enable_irq(PIT2_IRQn);                             //使能PIT2中断

  //舵机和电机初始化
  ftm_pwm_init(FTM1, FTM_CH0, 300, 4800); //PTA8舵机
  ftm_pwm_init(FTM0, FTM_CH2, 10000, 0);  //正转 PTA5 电机
  ftm_pwm_init(FTM0, FTM_CH3, 10000, 0);  //反转 PTA6 电机
  led(LED2, LED_OFF);
  //播码开关接口
  gpio_init(PTC1, GPI, 0);
  gpio_init(PTC2, GPI, 0);
  gpio_init(PTC3, GPI, 0);
  gpio_init(PTC4, GPI, 0);

  //测速模块初始化：正交解码、LPTMR_脉冲计数
  ftm_quad_init(FTM2); //A10和A11
  
  //串口初始化
  uart_init(UART4, 115200);

  //速度选择
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
