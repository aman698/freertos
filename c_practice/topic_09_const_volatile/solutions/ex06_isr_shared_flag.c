/*
 * ex06_isr_shared_flag.c — volatile flag between ISR and main loop
 * Key concept: flag set in ISR, cleared in main — must be volatile.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

static volatile bool button_pressed = false;

static void exti_isr_sim(void)
{
    button_pressed = true;
}

int main(void)
{
    exti_isr_sim();  /* Simulate EXTI on PC13 */

    if (button_pressed) {
        printf("Button event handled\n");
        button_pressed = false;
    }

    printf("Flag cleared: %s\n", button_pressed ? "set" : "clear");
    return 0;
}
