/**
 * Topic 06 - Exercise 11: Command string comparison
 * STM32 context: match USART commands to handlers
 * Build: gcc ex11_command_compare.c -o ex11 && ./ex11
 */
#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef enum {
    CMD_UNKNOWN = 0,
    CMD_LED_ON,
    CMD_LED_OFF
} Command_t;

static Command_t parse_command(const char *line)
{
    if (strcasecmp(line, "LED ON") == 0) {
        return CMD_LED_ON;
    }
    if (strcasecmp(line, "LED OFF") == 0) {
        return CMD_LED_OFF;
    }
    return CMD_UNKNOWN;
}

static const char *cmd_name(Command_t c)
{
    switch (c) {
    case CMD_LED_ON:  return "LED_ON";
    case CMD_LED_OFF: return "LED_OFF";
    default:          return "UNKNOWN";
    }
}

int main(void)
{
    const char *tests[] = { "LED ON", "led off", "STATUS", "LED ON " };
    const size_t n = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0U; i < n; i++) {
        Command_t cmd = parse_command(tests[i]);
        printf("Input=\"%s\" -> %s\n", tests[i], cmd_name(cmd));
    }
    return 0;
}
