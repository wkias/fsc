#include "include.h"

void config1()
{
}

void config2()
{
}

void config3()
{
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
        LCD_P6x8Str(COLUMN_1, 7, "S1");
    }
    if (gpio_get(PORT_SWITCHER_2) == 0)
    {
        config2();
        LCD_P6x8Str(COLUMN_1, 7, "S2");
    }
    if (gpio_get(PORT_SWITCHER_3) == 0)
    {
        config3();
        LCD_P6x8Str(COLUMN_1, 7, "S3");
    }
    if (gpio_get(PORT_SWITCHER_4) == 0)
    {
        config3();
        LCD_P6x8Str(COLUMN_1, 7, "S4");
    }
}

void dynamic_param(void)
{
}
