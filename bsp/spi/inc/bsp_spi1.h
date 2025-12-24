#ifndef BSP_SPI1_H
#define BSP_SPI1_H

#include <stdint.h>

/* CS LIS3DSH  */
void bsp_spi1_lis3dsh_cs_low(void);
void bsp_spi1_lis3dsh_cs_high(void);

/*  GPIO SPI1  */
void bsp_spi1_gpio_init(void);

/*  INIT SPI1  */
void bsp_spi1_spi_init(void);

/*  TRANSFER SPI1  */
uint8_t bsp_spi1_transfer(uint8_t data);

#endif 
