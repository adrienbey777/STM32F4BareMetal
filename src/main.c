/*
 * Copyright (c) 2025 BEY
 * Tous droits réservés.
 */

#include <stdint.h>
#include "spi/inc/spi.h"
#include "led/inc/led.h"

/* Mask combiné pour toutes les LEDs */
#define ALL_LEDS (LED_ORANGE | LED_RED | LED_GREEN | LED_BLUE)

/* Approx delay */
static void delay_approx(volatile unsigned int loops)
{
    volatile unsigned int i;
    for (i = 0; i < loops; ++i) {
        __asm__("nop");
    }
}


int main(void)
{
    /* Initialisations */
    led_init();
    spi_1_gpio_init();
    spi_1_init();
    spi_LIS3DSH_init();

    /* Vérif WHO_AM_I */

    led_off(ALL_LEDS);
    led_on(LED_GREEN);
    delay_approx(250000);
    led_off(LED_GREEN);

    /* Hystérésis */
    static uint8_t red_on = 0;
    static uint8_t green_on = 0;
    static uint8_t orange_on = 0;
    static uint8_t blue_on = 0;

    static int16_t x_raw, y_raw, z_raw;

    while (1)
    {
        spi_LIS3DSH_readxyz(&x_raw, &y_raw, &z_raw);

        /* Axe Y */
        if (!orange_on && y_raw > 1000) { led_on(LED_ORANGE); orange_on = 1; }
        else if (orange_on && y_raw < 800) { led_off(LED_ORANGE); orange_on = 0; }

        if (!blue_on && y_raw < -1000) { led_on(LED_BLUE); blue_on = 1; }
        else if (blue_on && y_raw > -800) { led_off(LED_BLUE); blue_on = 0; }

        /* Axe X */
        if (!red_on && x_raw > 1000) { led_on(LED_RED); red_on = 1; }
        else if (red_on && x_raw < 800) { led_off(LED_RED); red_on = 0; }

        if (!green_on && x_raw < -1000) { led_on(LED_GREEN); green_on = 1; }
        else if (green_on && x_raw > -800) { led_off(LED_GREEN); green_on = 0; }

        delay_approx(200000);
    }

    return 0;
}
