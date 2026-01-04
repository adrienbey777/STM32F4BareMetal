#include "driver_uart.h"

void driver_uart_enable_clock(USART_TypeDef *uart, uint32_t gpio_en, uint32_t uart_en) {
    RCC->AHB1ENR |= gpio_en;
    if (uart == USART1 || uart == USART6)
        RCC->APB2ENR |= uart_en;
    else
        RCC->APB1ENR |= uart_en;
}

void driver_uart_configure(USART_TypeDef *uart, uint32_t mantissa, uint32_t fraction) {
    uart->BRR = (mantissa << 4) | (fraction & 0xF);
    uart->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void driver_uart_send_char(USART_TypeDef *uart, char c) {
    while (!(uart->SR & USART_SR_TXE));
    uart->DR = (uint8_t)c;
}
