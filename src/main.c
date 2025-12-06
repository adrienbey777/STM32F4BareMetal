#include <stdio.h>
#include "uart/inc/uart.h"

void uart_send_string(const char *str) {
    while (*str) {
        uart_send(*str++);
    }
}

int main(void)
{
    uart_init();

    uart_send_string("Hello");

    while(1);
}
