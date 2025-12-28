#ifndef SPI1_H
#define SPI1_H

#include <stdint.h>

void spi1_init(void);
uint8_t spi1_transfer(uint8_t data);
void spi1_cs_low(void);
void spi1_cs_high(void);
#endif
