#ifndef BSP_SPI1_H
#define BSP_SPI1_H


/* CS LIS3DSH  */
void bsp_spi1_lis3dsh_cs_low(void);
void bsp_spi1_lis3dsh_cs_high(void);

/*  GPIO SPI1  */
void bsp_spi1_gpio_init(void);

#endif 
