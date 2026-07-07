/*
 * ex05_const_volatile.c — const volatile for read-only status registers
 * Key concept: HW may update register; firmware must not write it.
 */
#include <stdint.h>
#include <stdio.h>

static const volatile uint32_t UART_SR = 0x000000C0UL;  /* TXE|RXNE set */

int main(void)
{
    uint32_t sr = UART_SR;
    printf("UART SR = 0x%08lX\n", (unsigned long)sr);
    printf("TXE=%lu RXNE=%lu\n",
           (unsigned long)((sr >> 7) & 1UL),
           (unsigned long)((sr >> 5) & 1UL));
    return 0;
}
