#ifndef UART_H__
#define UART_H__

#include "MK70F12.h"

#define UART_2 UART2_BASE_PTR
#define UART_2_CLK 50000

extern void uart_init(UART_MemMapPtr uartChannel, int clockInKHz, int baud);
extern int uart_getchar_present (UART_MemMapPtr channel);
extern char uart_getchar (UART_MemMapPtr channel);
extern void uart_putchar (UART_MemMapPtr channel, char ch);


#endif
