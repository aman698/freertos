/*
 * ex01_basic_arithmetic.c — Timer period calculation
 * Key concept: integer division truncates; order matters for scaling.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t timer_clk_hz = 84000000UL;
    uint32_t prescaler    = 8399;   /* PSC register value (div = PSC+1) */
    uint32_t arr          = 999;    /* auto-reload */

    uint32_t div   = prescaler + 1;
    uint32_t ticks = arr + 1;
    uint32_t freq  = timer_clk_hz / div / ticks;

    printf("Timer clock: %lu Hz\n", (unsigned long)timer_clk_hz);
    printf("Prescaler:   %lu (divide by %lu)\n", (unsigned long)prescaler, (unsigned long)div);
    printf("ARR:         %lu (period %lu ticks)\n", (unsigned long)arr, (unsigned long)ticks);
    printf("Update freq: %lu Hz (~1 kHz)\n", (unsigned long)freq);

    return 0;
}
