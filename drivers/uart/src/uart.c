
/*
 * Copyright (c) 2025 BEY
 * Tous droits réservés.
 */
#include <stdint.h>
#include "../inc/uart.h"

// Registres STM32F407
#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)
#define RCC_APB1ENR (*(volatile uint32_t*)0x40023840)
#define GPIOA_MODER (*(volatile uint32_t*)0x40020000)
#define GPIOA_AFRL  (*(volatile uint32_t*)0x40020020)
#define GPIOA_ODR   (*(volatile uint32_t*)0x40020014)
#define USART2_SR  (*(volatile uint32_t*)0x40004400)
#define USART2_DR  (*(volatile uint32_t*)0x40004404)
#define USART2_BRR (*(volatile uint32_t*)0x40004408)
#define USART2_CR1 (*(volatile uint32_t*)0x4000440C)


#define USART_CR1_UE  (1 << 13)
#define USART_CR1_TE  (1 << 3)
#define USART_SR_TXE  (1 << 7)
#define USART_CR1_RE  (1 << 2)

// Fonction d'initialisation UART2 (PA2=TX)
void uart_init(void) {
    // 1. Activer l’horloge GPIOA et USART2
    RCC_AHB1ENR |= (1 << 0);  // GPIOAEN
    RCC_APB1ENR |= (1 << 17); // USART2EN

    // 2. Configurer PA2 en Alternate Function AF7 (USART2_TX)
    GPIOA_MODER &= ~(3 << (2*2));
    GPIOA_MODER |=  (2 << (2*2));
    GPIOA_AFRL  &= ~(0xF << (2*4));
    GPIOA_AFRL  |=  (7 << (2*4));

    // 3. Configurer baud rate = 115200, Fpclk1=42MHz
    // USARTDIV = 42MHz / (16 * 115200) ≈ 22.786
    uint32_t mantissa = 22;
    uint32_t fraction = 13; // 0.786*16 ≈ 12.57 -> 13
    USART2_BRR = (mantissa << 4) | (fraction & 0xF);

    // 4. Activer USART2, TX et RX
    USART2_CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

// Envoi d’un caractère
void uart_send(char c) {
    while (!(USART2_SR & USART_SR_TXE));
    USART2_DR = c;
}
