/*
 * ex10_volatile_struct.c — volatile struct for register block
 * Key concept: all struct members inherit volatile semantics when struct is volatile.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile uint32_t cr;
    volatile uint32_t sr;
    volatile uint32_t dr;
} volatile_uart_t;

int main(void)
{
    volatile_uart_t uart = { 0U, 0U, 0U };

    uart.cr = 0x00002000UL;
    uart.sr = 0x00000080UL;
    uart.dr = (uint32_t)'X';

    printf("CR=0x%08lX SR=0x%08lX DR='%c'\n",
           (unsigned long)uart.cr,
           (unsigned long)uart.sr,
           (char)uart.dr);
    return 0;
}
