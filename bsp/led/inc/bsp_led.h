#ifndef BSP_LED_H
#define BSP_LED_H

#include <stdint.h>

void bsp_led_init(void);
void bsp_led_on(uint8_t led);
void bsp_led_off(uint8_t led);
void bsp_led_toggle(uint8_t led);

#endif
