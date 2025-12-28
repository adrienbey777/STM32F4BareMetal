#include "bsp_uart.h"
#include "stm32f4xx.h"

static void bsp_uart_enable_clock(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
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

static void bsp_uart_configure(uint32_t baudrate)
{
    // Exemple pour 16 MHz / 115200
    uint32_t mantissa = 22;
    uint32_t fraction = 13;
    USART2->BRR = (mantissa << 4) | (fraction & 0xF);

    USART2->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void bsp_uart_send_char(char c)
{
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = (uint8_t)c;
}

void bsp_uart_init(uint32_t baudrate)
{
    bsp_uart_enable_clock();
    bsp_uart_init_pins();
    bsp_uart_configure(baudrate);
}