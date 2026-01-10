#include "driver_uart.h"

void driver_uart_enable_clock(USART_TypeDef *uart) {
    if (uart == USART2)RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}

void driver_uart_configure(USART_TypeDef *uart, uint32_t brr) {
    uart->CR1 = 0;
    uart->CR2 = 0;
    uart->CR3 = 0;
    uart->BRR = brr;   
    uart->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void driver_uart_send_char(USART_TypeDef *uart, char c) {
    while (!(USART2->SR & USART_SR_TXE)); // attendre TXE
    USART2->DR = (uint16_t)(c & 0xFF);   // 8 bits
     while (!(USART2->SR & USART_SR_TC));       // attendre fin transmission
}

