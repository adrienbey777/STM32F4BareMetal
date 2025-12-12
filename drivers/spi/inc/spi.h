#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// SPI1 (bus)
void spi_1_gpio_init(void);
void spi_1_init(void);
uint8_t spi_1_transfer(uint8_t data);

// LIS3DSH (driver capteur)
uint8_t spi_LIS3DSH_readreg(uint8_t reg);
void spi_LIS3DSH_writereg(uint8_t reg, uint8_t data);
void spi_LIS3DSH_init(void);
void spi_LIS3DSH_readxyz(int16_t *x, int16_t *y, int16_t *z);

#endif
