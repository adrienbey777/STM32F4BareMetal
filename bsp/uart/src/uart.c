
/*
 * Copyright (c) 2025 BEY
 * Tous droits réservés.
 */
#include "uart.h"
#include "stm32f4xx.h"  // CMSIS pour STM32F4

void uart_init(void) {
    // 1. Activer l’horloge GPIOA et USART2
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // GPIOA clock enable
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // USART2 clock enable

    // 2. Configurer PA2, PA3 en Alternate Function AF7 (USART2_TX) (USART2_RX)
    GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
    GPIOA->MODER |=  GPIO_MODER_MODE2_1;   // Alternate Function
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_Msk;
    GPIOA->AFR[0] |=  (7 << GPIO_AFRL_AFSEL2_Pos); // AF7 USART2

    GPIOA->MODER &= ~GPIO_MODER_MODE3_Msk;
    GPIOA->MODER |=  GPIO_MODER_MODE3_1;   // Alternate Function
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_Msk;
    GPIOA->AFR[0] |=  (7 << GPIO_AFRL_AFSEL3_Pos); // AF7 USART2

    // 4. Activer USART2, TX et RX
    uint32_t mantissa = 22;
    uint32_t fraction = 13; // 0.786*16 ≈ 12.57 -> 13
    USART2->BRR = (mantissa << 4) | (fraction & 0xF);

    USART2->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void uart_send(char c) {
    while (!(USART2->SR & USART_SR_TXE)); // Attente TXE
    USART2->DR = (uint8_t)c;
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_send(*str++);
    }
}