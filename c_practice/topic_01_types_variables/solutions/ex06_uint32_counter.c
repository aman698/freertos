/*
 * ex06_uint32_counter.c — 32-bit free-running system tick counter
 * Key concept: uint32_t gives ~49 days at 1 ms/tick before wrap.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t sys_tick_ms = 0;

    /* Simulate fast-forward: 1 hour of 1 ms ticks */
    sys_tick_ms = 3600000UL;

    printf("System tick: %lu ms\n", (unsigned long)sys_tick_ms);
    printf("Hours:       %lu\n", (unsigned long)(sys_tick_ms / 3600000UL));

    /* Near wrap (demo value) */
    sys_tick_ms = UINT32_MAX - 5;
    sys_tick_ms += 10; /* wraps — still defined for unsigned */
    printf("After wrap demo: %lu\n", (unsigned long)sys_tick_ms);

    printf("uint32_t max: %lu\n", (unsigned long)UINT32_MAX);
    return 0;
}
