/*
 * ex03_volatile_counter.c — volatile for variables changed by ISR/timer
 * Key concept: compiler must reload volatile from memory each read.
 */
#include <stdint.h>
#include <stdio.h>

static volatile uint32_t systick_ms = 0U;

static void systick_isr_sim(void)
{
    systick_ms++;
}

int main(void)
{
    for (int i = 0; i < 5; i++) {
        systick_isr_sim();
    }
    printf("systick_ms = %lu (updated by simulated ISR)\n",
           (unsigned long)systick_ms);
    return 0;
}
