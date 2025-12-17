/*
 * Copyright (c) 2025 BEY
 * Tous droits réservés.
 */

#include <stdint.h>
#include "spi/inc/spi.h"
#include "led/inc/led.h"
#include "uart/inc/uart.h"
#include "button/inc/button.h"

#define USE_MAIN 2


#define ALL_LEDS (LED_ORANGE | LED_RED | LED_GREEN | LED_BLUE)


static void delay_approx(volatile unsigned int loops)
{
    volatile unsigned int i;
    for (i = 0; i < loops; ++i) {
        __asm__("nop"); //__asm__ instruction assembleur dans du C, "nop" no operation, 1 cycle CPU
    }
}


static void main_1(void)
{
    
    static uint8_t red_on = 0u;
    static uint8_t green_on = 0u;
    static uint8_t orange_on = 0u;
    static uint8_t blue_on = 0u;

    static int16_t x_raw, y_raw, z_raw;

    spi_1_gpio_init();
    spi_1_init();
    spi_LIS3DSH_init();

    while (1)
    {
        spi_LIS3DSH_readxyz(&x_raw, &y_raw, &z_raw);

        /* Axe Y */
        if (!orange_on && y_raw > 1000) { led_on(LED_ORANGE); orange_on = 1u; }
        else if (orange_on && y_raw < 800) { led_off(LED_ORANGE); orange_on = 0u; }

        if (!blue_on && y_raw < -1000) { led_on(LED_BLUE); blue_on = 1u; }
        else if (blue_on && y_raw > -800) { led_off(LED_BLUE); blue_on = 0u; }

        /* Axe X */
        if (!red_on && x_raw > 1000) { led_on(LED_RED); red_on = 1u; }
        else if (red_on && x_raw < 800) { led_off(LED_RED); red_on = 0u; }

        if (!green_on && x_raw < -1000) { led_on(LED_GREEN); green_on = 1u; }
        else if (green_on && x_raw > -800) { led_off(LED_GREEN); green_on = 0u; }

        delay_approx(420000u); // 10ms at 168MHz
    }
}

static void main_2(void)
{
    button_init();
    uart_init();

    ButtonState last_raw = BUTTON_RESET;
    ButtonState stable   = BUTTON_RESET;
    uint8_t cnt = 0;

    uart_send_string("Begin\n"); 

    while (1)
    {
        ButtonState raw = button_read();

        if (raw == last_raw)
        {
            if (cnt < 5) cnt++;
            // Incrémente un compteur de stabilité (jusqu'à 5) 
            // Cela permet de s'assurer que le bouton est stable et évite
        }
        else
        {
            cnt = 0;
        }

        if (cnt >= 5)
        {
            if (raw == BUTTON_SET && stable == BUTTON_RESET)
            {
                stable = BUTTON_SET;
                led_toggle(LED_GREEN);
                uart_send_string("SET\n"); //Set
            }
            else if (raw == BUTTON_RESET && stable == BUTTON_SET)
            {
                stable = BUTTON_RESET;
                uart_send_string("RESET\n");   //Reset
            }
        }

        last_raw = raw;
        delay_approx(10000); // ~0.6ms at 168MHz
    }
    //UART RENODE
    //sysbus.gpioPortA.UserButton Press
    //sysbus.gpioPortA.UserButton Release
}



    int main(void)
    {
        led_init();
    // préprocesseur C, exécuté avant la compilation, selon la macro définie, un seul bloc est compilé
#if USE_MAIN == 1
        main_1();
#elif USE_MAIN == 2
        main_2();
#else
#error "USE_MAIN must be 1 or 2"
#endif

        while (1)
            ; /* sécurité */
    }
