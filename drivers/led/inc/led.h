#ifndef LED_H
#define LED_H
#include <stdint.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15

void led_init(void);
void led_toggle(uint8_t led);
void led_on(uint8_t led);
void led_off(uint8_t led);
#endif