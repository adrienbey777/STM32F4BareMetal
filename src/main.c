#include <stdio.h>
#include "uart/inc/uart.h"
#include "led/inc/led.h"

static void uart_send_string(const char *str) {
    while (*str) {
        uart_send(*str++);
    }
}
// Fonction de délai basique (busy-wait)
static void delay_ms(volatile unsigned int ms)
{
    for (unsigned int i = 0; i < ms; i++) {
        for (volatile unsigned int j = 0; j < 4000; j++) {
        }
    }
}

int main(void)
{

    uart_init();
    led_init();
    while (1) {
        //uart_send_string("Hello\n");
        uart_send('H');
        uart_send('\n'); 
        led_toggle();
        delay_ms(1000); // Délai de 1 seconde
    }
}