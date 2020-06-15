#include "include.h"

uint8 buff[DATA_PACKET];
uint8 rxlen;

void config1()
{
#ifdef FLASH_WRITE_PARAM
    flash_erase_sector(SECTOR_NO);
    flash_write(SECTOR_NO, 4, flash_read(SECTOR_NO, 4, FLASH_WRITE_TYPE) - 1);
    flash_write(SECTOR_NO, 0, 0x12345678);
#endif
}

void config2()
{
#ifdef FLASH_WRITE_PARAM
    flash_erase_sector(SECTOR_NO);
    flash_write(SECTOR_NO, 4, flash_read(SECTOR_NO, 4, FLASH_WRITE_TYPE) + 1);
    flash_write(SECTOR_NO, 0, 0x12345678);
#endif
}

void config3()
{
#ifdef FLASH_WRITE_PARAM
    flash_erase_sector(SECTOR_NO);
    flash_write(SECTOR_NO, 4, 1);
    flash_write(SECTOR_NO, 0, 0x12345678);
#endif
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
        LCD_P6x8Str(COLUMN_3, 7, "S1");
    }
    if (gpio_get(PORT_SWITCHER_2) == 0)
    {
        config2();
        LCD_P6x8Str(COLUMN_3, 7, "S2");
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
#ifdef ENABLE_NRF
    rxlen = nrf_rx(buff, DATA_PACKET);
    if (rxlen != 0){}
#endif
}