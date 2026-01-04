#include "spi1.h"
#include "bsp_spi1.h"


// Initialisation SPI1

void spi1_init(void)
{
    // Initialise les GPIO + CS
    bsp_spi1_gpio_init();

    // Initialise le SPI1 (CR1, Master, mode3…)
    bsp_spi1_spi_init();
}

// Transfert 1 octet

uint8_t spi1_transfer(uint8_t data)
{
    return bsp_spi1_transfer(data);
}

// CS control

void spi1_cs_low(void)
{
    bsp_spi1_lis3dsh_cs_low();
}

void spi1_cs_high(void)
{
    bsp_spi1_lis3dsh_cs_high();
}
