#include "include.h"

void config1()
{
    //TO-DO
}

void config2()
{
    //TO-DO
}

void config3()
{
    //TO-DO
}

void param_switcher()
{
    //速度选择
    if (gpio_get(PORT_SWITCHER_1) == 1)
    {
        config1();
        LCD_P6x8Str(COLUMN_1, 7, "S1");
    }
    if (gpio_get(PORT_SWITCHER_2) == 1)
    {
        config2();
        LCD_P6x8Str(COLUMN_1, 7, "S2");
    }
    if (gpio_get(PORT_SWITCHER_3) == 1)
    {
        config3();
        LCD_P6x8Str(COLUMN_1, 7, "S3");
    }
}

void dynamic_param(void)
{
    //TO-DO
}