#ifndef LED_H
#define LED_H

#include <stdint.h>

/* LEDs logiques */
typedef enum
{
    LED_GREEN,
    LED_ORANGE,
    LED_RED,
    LED_BLUE
} led_t;

/* API DRIVER */
void led_init(void);
void led_on(led_t led);
void led_off(led_t led);
void led_toggle(led_t led);

#endif
