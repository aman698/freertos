/*
 * ex01_simple_toggle_fsm.c - Toggle between LED states.
 * Key concept: enum names make states explicit.
 */
#include <stdio.h>

typedef enum {
    LED_OFF,
    LED_ON
} LedState_t;

int main(void)
{
    LedState_t state = LED_OFF;
    for (int i = 0; i < 4; i++) {
        state = (state == LED_OFF) ? LED_ON : LED_OFF;
        puts(state == LED_ON ? "LED ON" : "LED OFF");
    }
    return 0;
}
