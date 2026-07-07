/*
 * ex04_static_local.c — Static local retains value between calls
 * Key concept: static local = one instance for lifetime of program.
 */
#include <stdint.h>
#include <stdio.h>

static uint32_t tick_isr_sim(void)
{
    static uint32_t tick_count = 0U;
    tick_count++;
    return tick_count;
}

int main(void)
{
    for (int i = 0; i < 5; i++) {
        printf("Call %d: tick=%lu\n", i + 1, (unsigned long)tick_isr_sim());
    }
    return 0;
}
