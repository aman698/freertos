/*
 * ex05_while_poll.c — Poll status register until ready
 * Key concept: while loops until hardware flag is set (busy-wait pattern).
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Simulated volatile status register — bit 0 = TX ready */
    volatile uint32_t uart_sr = 0U;
    uint32_t poll_count = 0U;

    /* Simulate hardware setting flag after 5 polls */
    while ((uart_sr & 0x01U) == 0U) {
        poll_count++;
        if (poll_count == 5U) {
            uart_sr |= 0x01U;  /* TXE set — would happen in real HW */
        }
    }

    printf("UART TX ready after %lu polls\n", (unsigned long)poll_count);
    printf("SR = 0x%08lX\n", (unsigned long)uart_sr);
    return 0;
}
