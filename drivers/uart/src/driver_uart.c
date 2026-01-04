#include "driver_uart.h"

void driver_uart_enable_clock(USART_TypeDef *uart) {
    if (uart == USART2)RCC->APB2ENR |= RCC_APB1ENR_USART2EN;
}

void driver_uart_configure(USART_TypeDef *uart, uint32_t mantissa, uint32_t fraction) {
    uart->BRR = (mantissa << 4) | (fraction & 0xF);
    uart->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void driver_uart_send_char(USART_TypeDef *uart, char c) {
    while (!(uart->SR & USART_SR_TXE));
    uart->DR = (uint8_t)c;
}
