#ifndef BSP_UART_H
#define BSP_UART_H
#include <stdint.h>

void bsp_uart_send_char(char c);
void bsp_uart_init(uint32_t baudrate);
#endif
