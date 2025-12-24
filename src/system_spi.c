#include "system_spi.h"
#include "spi1.h"
#include "lis3dsh.h"

void system_spi_init(void)
{
    spi1_init();            // bus spi
    lis3dsh_init();         // capteur
}