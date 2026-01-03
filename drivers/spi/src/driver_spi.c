#include "driver_spi.h"

void driver_spi_enable_clock(SPI_TypeDef *spi) {
    if(spi == SPI1) RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
}

void driver_spi_configure(SPI_TypeDef *spi, uint32_t cr1_settings) {
    spi->CR1 = 0;
    spi->CR1 |= cr1_settings;
    spi->CR1 |= SPI_CR1_SPE; // enable
}

uint8_t driver_spi_transfer(SPI_TypeDef *spi, uint8_t data) {
    while (!(spi->SR & SPI_SR_TXE));
    *((volatile uint8_t *)&spi->DR) = data;

    while (!(spi->SR & SPI_SR_RXNE));
    uint8_t rx = *((volatile uint8_t *)&spi->DR);

    while (spi->SR & SPI_SR_BSY);
    return rx;
}
