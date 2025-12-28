#include "led.h"
#include "bsp_led.h"

void led_init(void)
{
    bsp_led_init();
}

void led_on(led_t led)
{
    bsp_led_on((uint8_t)led);
}

void led_off(led_t led)
{
    bsp_led_off((uint8_t)led);
}

void led_toggle(led_t led)
{
    bsp_led_toggle((uint8_t)led);
}
