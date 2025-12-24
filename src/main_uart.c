/*
 * Copyright (c) 2025 BEY
 * Tous droits réservés.
 */

#include <stdint.h>
#include "uart.h"
#include "main_uart.h"
#include "button.h"
#include "delay.h"
#include "led.h"

void main_uart(void)
{
    button_init();
    uart_init(115200u);

    ButtonState lLast_raw = BUTTON_RESET;
    ButtonState lStable   = BUTTON_RESET;
    uint8_t lCnt = 0;

    uart_send_string("Begin\n"); 

    while (1)
    {
        ButtonState lRaw = button_read();

        if (lRaw == lLast_raw)
        {
            if (lCnt < 5) lCnt++;
            // Incrémente un compteur de stabilité (jusqu'à 5) 
            // Cela permet de s'assurer que le bouton est lStable
        }
        else
        {
            lCnt = 0;
        }

        if (lCnt >= 5)
        {
            if (lRaw == BUTTON_SET && lStable == BUTTON_RESET)
            {
                lStable = BUTTON_SET;
                led_toggle(LED_GREEN);
                uart_send_string("SET\n"); //Set
            }
            else if (lRaw == BUTTON_RESET && lStable == BUTTON_SET)
            {
                lStable = BUTTON_RESET;
                uart_send_string("RESET\n");   //Reset
            }
        }

        lLast_raw = lRaw;
        delay(10000); // ~0.6ms at 168MHz
    }
    //UART RENODE
    //sysbus.gpioPortA.UserButton Press
    //sysbus.gpioPortA.UserButton Release
}