/*
 * ex03_switch_led_mode.c — LED blink mode selection
 * Key concept: switch dispatches on discrete mode enum values.
 */
#include <stdint.h>
#include <stdio.h>

typedef enum {
    LED_MODE_OFF = 0,
    LED_MODE_SLOW,
    LED_MODE_FAST
} led_mode_t;

static void apply_led_mode(led_mode_t mode)
{
    switch (mode) {
    case LED_MODE_OFF:
        printf("LD2 (PA5): OFF — ODR bit cleared\n");
        break;
    case LED_MODE_SLOW:
        printf("LD2 (PA5): SLOW blink — 500 ms period\n");
        break;
    case LED_MODE_FAST:
        printf("LD2 (PA5): FAST blink — 100 ms period\n");
        break;
    default:
        printf("Unknown mode — default to OFF\n");
        break;
    }
}

int main(void)
{
    apply_led_mode(LED_MODE_OFF);
    apply_led_mode(LED_MODE_SLOW);
    apply_led_mode(LED_MODE_FAST);
    return 0;
}
