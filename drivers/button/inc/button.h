#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#define BUTTON_PIN   0       // PA0
#define BUTTON_PORT  GPIOA   // port A
#define BUTTON_RCC   0       // RCC_AHB1ENR bit pour GPIOA

typedef enum {
    BUTTON_RESET = 0,
    BUTTON_SET
} ButtonState;

// Initialise le GPIO du bouton
void button_init(void);

// Lit l’état du bouton (0 ou 1)
ButtonState button_read(void);

#endif
