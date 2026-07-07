/*
 * ex09_optimization_trap.c — Without volatile, compiler may optimize away reads
 * Key concept: volatile forces load from memory — critical for polling HW flags.
 */
#include <stdint.h>
#include <stdio.h>

static volatile uint32_t hw_status = 0U;

static void hw_set_ready(void)
{
    hw_status = 1U;
}

int main(void)
{
    uint32_t polls = 0U;

    /* Simulate: flag set after a few polls */
    while ((hw_status & 1U) == 0U) {
        polls++;
        if (polls == 3U) {
            hw_set_ready();
        }
    }

    printf("Ready after %lu polls (volatile prevents stale cache)\n",
           (unsigned long)polls);
    return 0;
}
