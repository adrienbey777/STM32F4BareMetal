#include "stm32f4xx.h"
#include "driver_spi.h"
#include "bsp_spi1.h"

// CS LIS3DSH 
void bsp_spi1_lis3dsh_cs_low(void) {
    GPIOE->ODR &= ~(1 << 3);
}

void bsp_spi1_lis3dsh_cs_high(void) {
    GPIOE->ODR |= (1 << 3);
}

static void bsp_spi1_gpio_enable_clock(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN;
}

static void bsp_spi1_init_pins(void)
{
    // PA5, PA6, PA7 = AF5, SPI1 SCLK, MISO, MOSI
    GPIOA->MODER &= ~(
        GPIO_MODER_MODE5_Msk |
        GPIO_MODER_MODE6_Msk |
        GPIO_MODER_MODE7_Msk
    );

    GPIOA->MODER |= (
        (2 << GPIO_MODER_MODE5_Pos) |
        (2 << GPIO_MODER_MODE6_Pos) |
        (2 << GPIO_MODER_MODE7_Pos)
    );

    GPIOA->AFR[0] &= ~(
        (0xF << (5 * 4)) |
        (0xF << (6 * 4)) |
        (0xF << (7 * 4))
    );

    GPIOA->AFR[0] |= (
        (5 << (5 * 4)) |
        (5 << (6 * 4)) |
        (5 << (7 * 4))
    );

    // High speed for SPI pins
    GPIOA->OSPEEDR |= (
        (3 << GPIO_OSPEEDR_OSPEED5_Pos) |
        (3 << GPIO_OSPEEDR_OSPEED6_Pos) |
        (3 << GPIO_OSPEEDR_OSPEED7_Pos)
    );

    // Pull-down on MISO (PA6), no pull on others
    GPIOA->PUPDR &= ~(
        GPIO_PUPDR_PUPD5_Msk |
        GPIO_PUPDR_PUPD6_Msk |
        GPIO_PUPDR_PUPD7_Msk
    );

    GPIOA->PUPDR |= (2 << GPIO_PUPDR_PUPD6_Pos); // Pull-down MISO
}

static void bsp_spi1_init_cs(void)
{
    GPIOE->MODER &= ~GPIO_MODER_MODE3_Msk;
    GPIOE->MODER |=  (1 << GPIO_MODER_MODE3_Pos);
    GPIOE->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED3_Pos);
}


void bsp_spi1_gpio_init()
{
    bsp_spi1_gpio_enable_clock();
    bsp_spi1_init_pins();
    bsp_spi1_init_cs();
    bsp_spi1_lis3dsh_cs_high();
}

void bsp_spi1_spi_init(void)
{
    // Activer SPI1 clock
    driver_spi_enable_clock(SPI1);

    uint32_t cr1 = SPI_CR1_MSTR      |  // Master
                   SPI_CR1_SSM       |  // Software NSS
                   SPI_CR1_SSI       |  
                   SPI_CR1_CPOL      |  // Mode 3
                   SPI_CR1_CPHA      |
                   (0x4 << SPI_CR1_BR_Pos); // fPCLK/32
    driver_spi_configure(SPI1, cr1);
}

// Transfert SPI

uint8_t bsp_spi1_transfer(uint8_t data)
{
    return driver_spi_transfer(SPI1, data);
}