#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// SPI1 (bus)
void spi_1_gpio_init(void);
void spi_1_init(void);

// LIS3DSH (driver capteur)
void spi_LIS3DSH_init(void);
void spi_LIS3DSH_readxyz(int16_t *x, int16_t *y, int16_t *z);

#endif
