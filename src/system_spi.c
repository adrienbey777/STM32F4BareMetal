#include "system_spi.h"
#include "bsp_spi1.h"
#include "spi1.h"
#include "lis3dsh.h"

void system_spi_init(void)
{
    bsp_spi1_gpio_init();   // carte
    spi1_init();            // bus spi
    lis3dsh_init();         // capteur
}