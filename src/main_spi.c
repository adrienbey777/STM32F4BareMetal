/*
 * Copyright (c) 2025 BEY
 * Tous droits réservés.
 */

#include "main_spi.h"
#include "delay.h"
#include "led.h"
#include "lis3dsh.h"   
#include "spi1.h"

void main_spi(void)
{
    spi1_init();            // bus spi
    lis3dsh_init();         // capteur
    
    uint8_t lRed_on = 0u;
    uint8_t lGreen_on = 0u;
    uint8_t lOrange_on = 0u;
    uint8_t lBlue_on = 0u;

    int16_t lX_raw, lY_raw, lZ_raw;

    while (1)
    {
        lis3dsh_readxyz(&lX_raw, &lY_raw, &lZ_raw);

        /* Axe Y */
        if (!lOrange_on && lY_raw > 1000) { led_on(LED_ORANGE); lOrange_on = 1u; }
        else if (lOrange_on && lY_raw < 800) { led_off(LED_ORANGE); lOrange_on = 0u; }

        if (!lBlue_on && lY_raw < -1000) { led_on(LED_BLUE); lBlue_on = 1u; }
        else if (lBlue_on && lY_raw > -800) { led_off(LED_BLUE); lBlue_on = 0u; }

        /* Axe X */
        if (!lRed_on && lX_raw > 1000) { led_on(LED_RED); lRed_on = 1u; }
        else if (lRed_on && lX_raw < 800) { led_off(LED_RED); lRed_on = 0u; }

        if (!lGreen_on && lX_raw < -1000) { led_on(LED_GREEN); lGreen_on = 1u; }
        else if (lGreen_on && lX_raw > -800) { led_off(LED_GREEN); lGreen_on = 0u; }

        delay(420000u); // 10ms at 168MHz
    }
}