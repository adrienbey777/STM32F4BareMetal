#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "stm32f4xx.h"
#include <stdint.h>

// Active les horloges
void driver_uart_enable_clock(USART_TypeDef *uart, uint32_t gpio_en, uint32_t uart_en);

// Configure BRR et CR1
void driver_uart_configure(USART_TypeDef *uart, uint32_t mantissa, uint32_t fraction);

// Envoi
void driver_uart_send_char(USART_TypeDef *uart, char c);

#endif
