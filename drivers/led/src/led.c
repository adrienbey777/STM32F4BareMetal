#include "../inc/led.h"

#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)

#define GPIOD_MODER (*(volatile uint32_t*)0x40020C00)
#define GPIOD_ODR (*(volatile uint32_t*)0x40020C14)


// Initialisation LED sur PA5
void led_init(void) {
        // GPIODEN = bit 3
    RCC_AHB1ENR |= (1 << 3); 

    GPIOD_MODER &= ~((3<< (LED_GREEN*2)) |
                     (3<< (LED_ORANGE*2)) |
                     (3<< (LED_RED*2)) |
                     (3<< (LED_BLUE*2)));
    GPIOD_MODER |=  ((1<< (LED_GREEN*2)) |
                     (1<< (LED_ORANGE*2)) |
                     (1<< (LED_RED*2)) |
                     (1<< (LED_BLUE*2)));
}

// Toggle LED
void led_toggle(void) {
    GPIOD_ODR ^= (1 << LED_GREEN) |
                 (1 << LED_ORANGE) |
                 (1 << LED_RED) |
                 (1 << LED_BLUE);
}

// Allumer une LED spécifique
void led_on(uint8_t led) {
    GPIOD_ODR |= (1 << led);
}

// Éteindre une LED spécifique
void led_off(uint8_t led) {
    GPIOD_ODR &= ~(1 << led);
}