/*
 * ex01_fixed_array_table.c - Store config rows in a fixed table.
 * Key concept: arrays are simple deterministic data structures.
 */
#include <stdio.h>

typedef struct {
    const char *name;
    unsigned pin;
} PinConfig_t;

int main(void)
{
    const PinConfig_t pins[] = {{"LED", 5U}, {"BUTTON", 13U}, {"UART_TX", 2U}};
    for (size_t i = 0U; i < sizeof(pins) / sizeof(pins[0]); i++) {
        printf("%s pin %u\n", pins[i].name, pins[i].pin);
    }
    return 0;
}
