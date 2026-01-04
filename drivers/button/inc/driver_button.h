#ifndef DRIVER_BUTTON_H
#define DRIVER_BUTTON_H

#include "stm32f4xx.h"
#include <stdint.h>

// Activer l'horloge pour un port GPIO
void driver_button_enable_clock(GPIO_TypeDef *port, uint32_t en_mask);

// Configurer le mode d'une pin (0=input, 1=output, 2=AF, 3=analog)
void driver_button_set_mode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);

// Lire l'état d'une pin (0 ou 1)
uint8_t driver_button_read_pin(GPIO_TypeDef *port, uint8_t pin);

#endif
