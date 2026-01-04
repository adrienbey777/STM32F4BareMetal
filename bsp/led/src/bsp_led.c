// bsp_led.c
#include "bsp_led.h"
#include "driver_gpio.h"

static const uint8_t bsp_led_pin[] = {12, 13, 14, 15};
#define BSP_LED_PORT GPIOD

void bsp_led_init(void) {
    driver_gpio_enable_clock(BSP_LED_PORT);
    for(int i=0; i<4; i++) {
        driver_gpio_set_mode(BSP_LED_PORT, bsp_led_pin[i], 1u); 
    }
}

void bsp_led_on(uint8_t led) {
    driver_gpio_write_pin(BSP_LED_PORT, bsp_led_pin[led], 1u);
}

void bsp_led_off(uint8_t led) {
    driver_gpio_write_pin(BSP_LED_PORT, bsp_led_pin[led], 0u);
}

void bsp_led_toggle(uint8_t led) {
    driver_gpio_toggle_pin(BSP_LED_PORT, bsp_led_pin[led]);
}
