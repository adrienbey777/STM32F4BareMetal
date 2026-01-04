#include "driver_led.h"

void driver_led_enable_clock(GPIO_TypeDef *port, uint32_t en_mask)
{
    if (port == GPIOD)
        RCC->AHB1ENR |= en_mask;
}

void driver_led_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
    port->MODER &= ~(3U << (pin * 2));
    port->MODER |= (mode << (pin * 2));
}

void driver_led_write_pin(GPIO_TypeDef *port, uint8_t pin, uint8_t value)
{
    if (value)
        port->ODR |= (1U << pin); // Set high
    else
        port->ODR &= ~(1U << pin); // Set low
}

void driver_led_toggle_pin(GPIO_TypeDef *port, uint8_t pin)
{
    port->ODR ^= (1U << pin);
}
