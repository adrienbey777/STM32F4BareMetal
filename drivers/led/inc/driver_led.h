
#ifndef DRIVER_LED_H
#define DRIVER_LED_H
#include <stdint.h>
#include "stm32f4xx.h"

void driver_led_enable_clock(GPIO_TypeDef *port, uint32_t en_mask);
void driver_led_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
void driver_led_write_pin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);
void driver_led_toggle_pin(GPIO_TypeDef *port, uint8_t pin);

#endif
