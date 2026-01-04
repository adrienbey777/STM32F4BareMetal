#ifndef DRIVER_SPI_H
#define DrIVER_SPI_H

#include "stm32f4xx.h"
#include <stdint.h>

void driver_spi_enable_clock(SPI_TypeDef *spi);
void driver_spi_configure(SPI_TypeDef *spi, uint32_t cr1_settings);

uint8_t driver_spi_transfer(SPI_TypeDef *spi, uint8_t data);

#endif
