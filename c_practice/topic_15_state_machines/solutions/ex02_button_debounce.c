/*
 * ex02_button_debounce.c - Debounce noisy button samples.
 * Key concept: require stable samples before accepting a press.
 */
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    BTN_RELEASED,
    BTN_DEBOUNCE,
    BTN_PRESSED
} ButtonState_t;

int main(void)
{
    bool samples[] = {false, true, false, true, true, true};
    ButtonState_t state = BTN_RELEASED;
    unsigned stable = 0U;

    for (size_t i = 0U; i < sizeof(samples) / sizeof(samples[0]); i++) {
        switch (state) {
        case BTN_RELEASED:
            if (samples[i]) {
                state = BTN_DEBOUNCE;
                stable = 1U;
            }
            break;
        case BTN_DEBOUNCE:
            stable = samples[i] ? stable + 1U : 0U;
            if (stable >= 3U) {
                state = BTN_PRESSED;
                puts("button pressed");
            }
            break;
        case BTN_PRESSED:
            break;
        }
    }
    return 0;
}
