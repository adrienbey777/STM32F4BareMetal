#include "uart.h"
#include "bsp_uart.h"

void uart_init(uint32_t baudrate)
{
    bsp_uart_init(baudrate);
}

void uart_send_char(char c)
{
    bsp_uart_send_char(c);
}

void uart_send_string(const char *s)
{
    while (*s)
    {
        uart_send_char(*s++);
    }
}

