/*
 * ex12_embedded_flags.c — Multiple volatile event flags
 * Key concept: bitmask or separate volatiles for ISR-to-task signaling.
 */
#include <stdint.h>
#include <stdio.h>

static volatile uint32_t event_flags = 0U;

#define EVT_UART_RX  (1UL << 0)
#define EVT_TIMER    (1UL << 1)
#define EVT_BUTTON   (1UL << 2)

static void simulate_isrs(void)
{
    event_flags |= EVT_UART_RX;
    event_flags |= EVT_BUTTON;
}

int main(void)
{
    simulate_isrs();

    if (event_flags & EVT_UART_RX) {
        printf("Handle UART RX\n");
        event_flags &= ~EVT_UART_RX;
    }
    if (event_flags & EVT_BUTTON) {
        printf("Handle button\n");
        event_flags &= ~EVT_BUTTON;
    }

    printf("Remaining flags = 0x%08lX\n", (unsigned long)event_flags);
    return 0;
}
