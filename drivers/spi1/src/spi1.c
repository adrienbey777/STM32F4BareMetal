#include "stm32f4xx.h" 
#include "spi1.h"


void spi1_init(void)
{
    // Horloge SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 = 0;
    SPI1->CR1 |= SPI_CR1_MSTR;               // Master
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  // Software NSS
    SPI1->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA; // Mode 3
    SPI1->CR1 |= (0x4 << SPI_CR1_BR_Pos);    // fPCLK/32
    SPI1->CR1 |= SPI_CR1_SPE;                // Enable
}

uint8_t spi1_transfer(uint8_t data)
{
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_RXNE));
    return SPI1->DR;
}
