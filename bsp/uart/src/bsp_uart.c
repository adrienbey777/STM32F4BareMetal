#include "bsp_uart.h"
#include "driver_uart.h"
#include "stm32f4xx.h"

static void bsp_uart_enable_clock(void)
{
    driver_uart_enable_clock(USART2, RCC_AHB1ENR_GPIOAEN, RCC_APB1ENR_USART2EN);
}

static void bsp_uart_init_pins(void)
{
    // PA2 TX
    GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE2_1;
    GPIOA->AFR[0] &= ~(0xF << GPIO_AFRL_AFSEL2_Pos);
    GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos);

    // PA3 RX
    GPIOA->MODER &= ~GPIO_MODER_MODE3_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE3_1;
    GPIOA->AFR[0] &= ~(0xF << GPIO_AFRL_AFSEL3_Pos);
    GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL3_Pos);
}

static void bsp_uart_configure(uint32_t baudrate) {
    // Exemple 16 MHz / 115200
    uint32_t mantissa = 22;
    uint32_t fraction = 13;
    driver_uart_configure(USART2, mantissa, fraction);
}

void bsp_uart_init(uint32_t baudrate) {
    bsp_uart_enable_clock();
    bsp_uart_init_pins();
    bsp_uart_configure(baudrate);
}

void bsp_uart_send_char(char c) {
    driver_uart_send_char(USART2, c);
}