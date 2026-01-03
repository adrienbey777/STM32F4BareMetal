#include "driver_button.h"

void driver_button_enable_clock(GPIO_TypeDef *port, uint32_t en_mask) {
    if (port == GPIOA) RCC->AHB1ENR |= en_mask;
}

void driver_button_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode) {
    port->MODER &= ~(3U << (pin * 2));   // clear
    port->MODER |= (mode << (pin * 2));  // set
}

uint8_t driver_button_read_pin(GPIO_TypeDef *port, uint8_t pin) {
    if ((port->IDR & (1U << pin)) != 0) {
        return 1U;
    } else {
        return 0U;
    }
}
