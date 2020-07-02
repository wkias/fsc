#include "include.h"

int8 switch_ch[5] = "S    ";

void config1()
{
    motor_protection_switcher = 0;
}

void config2()
{
}

void config3()
{
}

void param_switcher()
{
    gpio_init(PORT_SWITCHER_1, GPO, 0);
    gpio_init(PORT_SWITCHER_2, GPO, 0);
    gpio_init(PORT_SWITCHER_3, GPO, 0);
    gpio_init(PORT_SWITCHER_4, GPO, 0);

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
        config3();
        switch_ch[4] = '4';
    }
}

void dynamic_param(void)
{
}
