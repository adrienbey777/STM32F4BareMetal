#include <stdint.h>
#include "../inc/uart.h"

// Registres STM32F407
#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)
#define RCC_APB1ENR (*(volatile uint32_t*)0x40023840)
#define GPIOA_MODER (*(volatile uint32_t*)0x40020000)
#define GPIOA_AFRL  (*(volatile uint32_t*)0x40020020)
#define USART2_SR  (*(volatile uint32_t*)0x40004400)
#define USART2_DR  (*(volatile uint32_t*)0x40004404)
#define USART2_BRR (*(volatile uint32_t*)0x40004408)
#define USART2_CR1 (*(volatile uint32_t*)0x4000440C)

#define USART_CR1_TE (1 << 3)
#define USART_CR1_UE (1 << 13)
#define USART_SR_TXE (1 << 7)

void uart_init(void) {

    // Activer l'horloge du GPIOA
    RCC_AHB1ENR |= (1 << 0);

    // Activer l'horloge de l'USART2
    RCC_APB1ENR |= (1 << 17);

    // Effacer les 2 bits du MODER pour PA2
    GPIOA_MODER &= ~(3 << (2*2));

    // Mettre PA2 en Alternate Function
    GPIOA_MODER |=  (2 << (2*2));

    // Sélectionner la fonction alternative AF7 sur PA2
    GPIOA_AFRL |=  (7 << (2*4));

    // Configurer le baud rate (Fpclk1=42MHz, Baud=115200)
    USART2_BRR = 42000000 / 115200;

    // Activer l’USART2 et le transmetteur
    USART2_CR1 = USART_CR1_TE | USART_CR1_UE; 
}

void uart_send(char c) {

    // Attendre que TXE = 1
    while (!(USART2_SR & USART_SR_TXE))
        ;

    // Écrire l’octet dans le Data Register
    USART2_DR = c;
}
