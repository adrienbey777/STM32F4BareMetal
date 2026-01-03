// bsp_led.c
#include "bsp_led.h"
#include "driver_led.h"

static const uint8_t bsp_led_pin[] = {12, 13, 14, 15};
#define BSP_LED_PORT GPIOD
#define BSP_LED_PORT_CLK RCC_AHB1ENR_GPIODEN

void bsp_led_init(void) {
    driver_led_enable_clock(BSP_LED_PORT, BSP_LED_PORT_CLK);
    for(int i=0; i<4; i++) {
        driver_led_set_mode(BSP_LED_PORT, bsp_led_pin[i], 1); // 1=output
    }
}

void bsp_led_on(uint8_t led) {
    driver_led_write_pin(BSP_LED_PORT, bsp_led_pin[led], 1);
}

void bsp_led_off(uint8_t led) {
    driver_led_write_pin(BSP_LED_PORT, bsp_led_pin[led], 0);
}

void bsp_led_toggle(uint8_t led) {
    driver_led_toggle_pin(BSP_LED_PORT, bsp_led_pin[led]);
}
