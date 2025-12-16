/*
 * Copyright (c) 2025 BEY
 * Tous droits réservés.
 */
#include <stdint.h>
#include "../inc/spi.h"
#include "stm32f4xx.h"  // CMSIS pour STM32F4

// LIS3DSH constants
#define LIS3DSH_CS_LOW()   (GPIOE->ODR &= ~(1 << 3))
#define LIS3DSH_CS_HIGH()  (GPIOE->ODR |=  (1 << 3))
#define LIS3DSH_WHO_AM_I   0x0F
#define LIS3DSH_CTRL_REG4  0x20
#define LIS3DSH_CTRL_REG5  0x24
#define LIS3DSH_OUT_X_L    0x28

// PA5=SCK, PA6=MISO, PA7=MOSI, PE3=CS
void spi_1_gpio_init(void) {
    // Activer horloge GPIOA et GPIOE
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN;

    // PA5, PA6, PA7 = AF5 (SPI1)
    GPIOA->MODER &= ~((GPIO_MODER_MODE5_Msk) | (GPIO_MODER_MODE6_Msk) | (GPIO_MODER_MODE7_Msk));
    GPIOA->MODER |=  ((2 << GPIO_MODER_MODE5_Pos) | (2 << GPIO_MODER_MODE6_Pos) | (2 << GPIO_MODER_MODE7_Pos));
    GPIOA->AFR[0] &= ~((0xF << (5*4)) | (0xF << (6*4)) | (0xF << (7*4)));
    GPIOA->AFR[0] |=  ((5 << (5*4)) | (5 << (6*4)) | (5 << (7*4)));

    // PE3 = CS → output, high speed
    GPIOE->MODER &= ~(GPIO_MODER_MODE3_Msk);
    GPIOE->MODER |=  (1 << GPIO_MODER_MODE3_Pos);
    GPIOE->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED3_Pos);

    LIS3DSH_CS_HIGH(); // Deselect LIS3DSH
}

void spi_1_init(void) {
    // Activer horloge SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 = 0;
    SPI1->CR1 |= SPI_CR1_MSTR;       // Master mode
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI; // Software slave management
    SPI1->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA; // CPOL=1, CPHA=1
    SPI1->CR1 |= (0x4 << SPI_CR1_BR_Pos);    // Baud rate = fPCLK/32
    SPI1->CR1 |= SPI_CR1_SPE;        // Enable SPI
}

// SPI transfer
static uint8_t spi_1_transfer(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE)); // Attente TXE
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_RXNE)); // Attente RXNE
    return SPI1->DR;
}

// LIS3DSH write
static void spi_LIS3DSH_writereg(uint8_t reg, uint8_t data) {
    LIS3DSH_CS_LOW();
    spi_1_transfer(reg & 0x3F); // write
    spi_1_transfer(data);
    LIS3DSH_CS_HIGH();
}

// LIS3DSH read
static uint8_t spi_LIS3DSH_readreg(uint8_t reg) {
    uint8_t val;
    LIS3DSH_CS_LOW();
    spi_1_transfer(0x80 | reg); // read bit7=1
    val = spi_1_transfer(0x00);
    LIS3DSH_CS_HIGH();
    return val;
}

// LIS3DSH init
void spi_LIS3DSH_init(void) {
    uint8_t id = spi_LIS3DSH_readreg(LIS3DSH_WHO_AM_I);
    if (id != 0x3F) return;

    spi_LIS3DSH_writereg(LIS3DSH_CTRL_REG4, 0xE7); // 100Hz, XYZ enable, BDU=1
    spi_LIS3DSH_writereg(LIS3DSH_CTRL_REG5, 0x00); // ±2g
}

// Lire les 3 axes
void spi_LIS3DSH_readxyz(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t xl, xh, yl, yh, zl, zh;

    LIS3DSH_CS_LOW();
    spi_1_transfer(0x80 | LIS3DSH_OUT_X_L);

    xl = spi_1_transfer(0x00);
    xh = spi_1_transfer(0x00);
    yl = spi_1_transfer(0x00);
    yh = spi_1_transfer(0x00);
    zl = spi_1_transfer(0x00);
    zh = spi_1_transfer(0x00);
    LIS3DSH_CS_HIGH();

    *x = (int16_t)((xh << 8) | xl);
    *y = (int16_t)((yh << 8) | yl);
    *z = (int16_t)((zh << 8) | zl);
}

