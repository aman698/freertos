/*
 * ex11_command_parser.c - Text command table with handler functions.
 * Key concept: map strings to functions.
 */
#include <stdio.h>
#include <string.h>

typedef void (*Handler_t)(void);

typedef struct {
    const char *name;
    Handler_t handler;
} Command_t;

static void led_on(void)  { puts("LED on"); }
static void led_off(void) { puts("LED off"); }

int main(void)
{
    const Command_t commands[] = {{"on", led_on}, {"off", led_off}};
    const char *input = "on";

    for (size_t i = 0U; i < sizeof(commands) / sizeof(commands[0]); i++) {
        if (strcmp(input, commands[i].name) == 0) {
            commands[i].handler();
        }
    }
    return 0;
}
