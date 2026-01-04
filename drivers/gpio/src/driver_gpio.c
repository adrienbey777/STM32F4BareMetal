#include "driver_gpio.h"

void driver_gpio_enable_clock(GPIO_TypeDef *port)
{
    if (port == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if (port == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}

void driver_gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
    port->MODER &= ~(3U << (pin * 2));
    port->MODER |= (mode << (pin * 2));
}

void driver_gpio_write_pin(GPIO_TypeDef *port, uint8_t pin, uint8_t value)
{
    if (value)
        port->ODR |= (1U << pin);
    else
        port->ODR &= ~(1U << pin);
}

void driver_gpio_toggle_pin(GPIO_TypeDef *port, uint8_t pin)
{
    port->ODR ^= (1U << pin);
}

uint8_t driver_gpio_read_pin(GPIO_TypeDef *port, uint8_t pin)
{
    if ((port->IDR & (1U << pin)) != 0u)
    {
        return 1u;
    }
    else
    {
        return 0u;
    }
}
