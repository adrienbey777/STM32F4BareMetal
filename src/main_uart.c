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
#include "system.h"

void main_uart(void)
{
    system_init();
    button_init();
    uart_init(115200u);

    ButtonEvent lEvent;

    uart_send_string("Begin\n"); 

    while (1)
    {
        lEvent = button_update();
        if (lEvent == BUTTON_EVENT_SET)
        {
            led_toggle(LED_GREEN);
            uart_send_string("SET\n"); // Set
        }
        else if (lEvent == BUTTON_EVENT_RESET)
        {
            uart_send_string("RESET\n"); // Reset
        }
        delay(10000u); // ~0.6ms at 168MHz
    }
    //UART RENODE
    //sysbus.gpioPortA.UserButton Press
    //sysbus.gpioPortA.UserButton Release
}