#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include "stm32f4xx.h"


void driver_gpio_enable_clock(GPIO_TypeDef *port);
void driver_gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
void driver_gpio_write_pin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);
void driver_gpio_toggle_pin(GPIO_TypeDef *port, uint8_t pin);
uint8_t driver_gpio_read_pin(GPIO_TypeDef *port, uint8_t pin);

#endif
