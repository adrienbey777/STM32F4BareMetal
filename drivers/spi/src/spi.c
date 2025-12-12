#include <stdint.h>
#include "../inc/spi.h"

// Base addresses
#define RCC_AHB1ENR  (*(volatile uint32_t*)0x40023830)
#define RCC_APB2ENR  (*(volatile uint32_t*)0x40023844)

// GPIOA : SPI1 (SCK, MISO, MOSI)
// GPIOE : CS
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define GPIOA_AFRL    (*(volatile uint32_t*)0x40020020)
#define GPIOE_MODER   (*(volatile uint32_t*)0x40021000)
#define GPIOE_ODR     (*(volatile uint32_t*)0x40021014)
#define GPIOE_OSPEEDR (*(volatile uint32_t*)0x40021008)

// SPI1 registers
#define SPI1_CR1     (*(volatile uint32_t*)0x40013000)
#define SPI1_CR2     (*(volatile uint32_t*)0x40013004)
#define SPI1_SR      (*(volatile uint32_t*)0x40013008)
#define SPI1_DR      (*(volatile uint32_t*)0x4001300C)

// LIS3DSH constants
#define LIS3DSH_CS_LOW()   (GPIOE_ODR &= ~(1 << 3))
#define LIS3DSH_CS_HIGH()  (GPIOE_ODR |=  (1 << 3))

#define LIS3DSH_WHO_AM_I   0x0F
#define LIS3DSH_CTRL_REG4  0x20
#define LIS3DSH_CTRL_REG5  0x24
#define LIS3DSH_OUT_X_L    0x28

// PA5=SCK, PA6=MISO, PA7=MOSI, PE3=CS
void spi_1_gpio_init(void) {
    RCC_AHB1ENR |= (1 << 0) | (1 << 4); // Enable GPIOA + GPIOE clock

    // PA5, PA6, PA7 = AF5 (SPI1)
    GPIOA_MODER &= ~((3 << (5*2)) | (3 << (6*2)) | (3 << (7*2)));
    GPIOA_MODER |=  ((2 << (5*2)) | (2 << (6*2)) | (2 << (7*2)));
    GPIOA_AFRL  &= ~((0xF << (5*4)) | (0xF << (6*4)) | (0xF << (7*4)));
    GPIOA_AFRL  |=  ((5 << (5*4)) | (5 << (6*4)) | (5 << (7*4)));

    // PE3 = CS → output
    GPIOE_MODER &= ~(3 << (3*2));
    GPIOE_MODER |=  (1 << (3*2));
    GPIOE_OSPEEDR |= (3 << (3*2)); // High speed
    LIS3DSH_CS_HIGH(); // Deselect LIS3DSH
}

void spi_1_init(void) {
    RCC_APB2ENR |= (1 << 12); // Enable SPI1 clock

    SPI1_CR1 = 0;
    SPI1_CR1 |= (1 << 2);      // Master mode
    SPI1_CR1 |= (1 << 8) | (1 << 9); // Software slave management
    SPI1_CR1 |= (1 << 1);      // CPOL = 1
    SPI1_CR1 |= (1 << 0);      // CPHA = 1
    SPI1_CR1 |= (0x4 << 3);    // Baud rate = fPCLK/32
    SPI1_CR1 |= (1 << 6);      // Enable SPI
}

//  SPI transfer 
uint8_t spi_1_transfer(uint8_t data) {
    while (!(SPI1_SR & (1 << 1))); // Wait TXE
    SPI1_DR = data;
    while (!(SPI1_SR & (1 << 0))); // Wait RXNE
    return SPI1_DR;
}

// LIS3DSH write
void spi_LIS3DSH_writereg(uint8_t reg, uint8_t data) {
    LIS3DSH_CS_LOW();
    spi_1_transfer(reg & 0x3F); // write
    spi_1_transfer(data);
    LIS3DSH_CS_HIGH();
}

// LIS3DSH read 
uint8_t spi_LIS3DSH_readreg(uint8_t reg) {
    uint8_t val;
    LIS3DSH_CS_LOW();
    spi_1_transfer(0x80 | reg); // read bit7=1
    val = spi_1_transfer(0x00);
    LIS3DSH_CS_HIGH();
    return val;
}

//  LIS3DSH init 
void spi_LIS3DSH_init(void) {
    uint8_t id = spi_LIS3DSH_readreg(LIS3DSH_WHO_AM_I);
    if (id != 0x3F) {
        return;
    }
    spi_LIS3DSH_writereg(LIS3DSH_CTRL_REG4, 0x67); // 100Hz, XYZ enable
    spi_LIS3DSH_writereg(LIS3DSH_CTRL_REG5, 0x00); // ±2g
}

// --- Lire les 3 axes ---
void spi_LIS3DSH_readxyz(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t xl, xh, yl, yh, zl, zh;

    LIS3DSH_CS_LOW();
    spi_1_transfer(0xC0 | LIS3DSH_OUT_X_L); // Read + auto-increment
    xl = spi_1_transfer(0);
    xh = spi_1_transfer(0);
    yl = spi_1_transfer(0);
    yh = spi_1_transfer(0);
    zl = spi_1_transfer(0);
    zh = spi_1_transfer(0);
    LIS3DSH_CS_HIGH();

    *x = (int16_t)((xh << 8) | xl);
    *y = (int16_t)((yh << 8) | yl);
    *z = (int16_t)((zh << 8) | zl);
}
