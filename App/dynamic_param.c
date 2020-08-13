#include "include.h"

int8 switch_ch[] = "S    ";
int rotary_road_time = 0;

void config1()
{
    // motor_protection_switcher = 0;
    rotary_road_time += 50;
}

void config2()
{
    // light_switcher = 0;
    rotary_road_time += 100;
}

void config3()
{
    // rotary_road_switcher = 0;
    rotary_road_time += 200;
}

void config4()
{
    rotary_road_time += 400;
}

void param_switcher()
{
    gpio_init(PORT_SWITCHER_1, GPI, 0);
    gpio_init(PORT_SWITCHER_2, GPI, 0);
    gpio_init(PORT_SWITCHER_3, GPI, 0);
    gpio_init(PORT_SWITCHER_4, GPI, 0);

    if (gpio_get(PORT_SWITCHER_1) == 0)
    {
        config1();
        switch_ch[1] = '1';
    }
    if (gpio_get(PORT_SWITCHER_2) == 0)
    {
        config2();
        switch_ch[2] = '2';
    }
    if (gpio_get(PORT_SWITCHER_3) == 0)
    {
        config3();
        switch_ch[3] = '3';
    }
    if (gpio_get(PORT_SWITCHER_4) == 0)
    {
        config4();
        switch_ch[4] = '4';
    }
}

void dynamic_param(void)
{
}
