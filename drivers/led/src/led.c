#include "stm32f4xx.h"  // CMSIS pour STM32F4
#include "led.h"

// Initialisation LEDs sur GPIOD
void led_init(void) {
    // Activer horloge GPIOD
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // Configurer les pins en output
    GPIOD->MODER &= ~((3 << (LED_GREEN*2)) |
                      (3 << (LED_ORANGE*2)) |
                      (3 << (LED_RED*2)) |
                      (3 << (LED_BLUE*2)));

    GPIOD->MODER |=  ((1 << (LED_GREEN*2)) |
                      (1 << (LED_ORANGE*2)) |
                      (1 << (LED_RED*2)) |
                      (1 << (LED_BLUE*2)));
}

// Toggle une LED spécifique
void led_toggle(uint8_t led)
{
    GPIOD->ODR ^= (1 << led);
}

// Allumer une LED spécifique
void led_on(uint8_t led)
{
    GPIOD->ODR |= (1 << led);
}

// Éteindre une LED spécifique
void led_off(uint8_t led)
{
    GPIOD->ODR &= ~(1 << led);
}
