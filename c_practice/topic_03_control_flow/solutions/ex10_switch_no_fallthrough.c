/*
 * ex10_switch_no_fallthrough.c — UART command dispatch
 * Key concept: each switch case ends with break to avoid fall-through.
 */
#include <stdint.h>
#include <stdio.h>

static void handle_command(char cmd)
{
    printf("Command '%c': ", cmd);

    switch (cmd) {
    case 's':
        printf("START measurement\n");
        break;
    case 'h':
        printf("HALT measurement\n");
        break;
    case 'r':
        printf("RESET counters\n");
        break;
    case '?':
        printf("HELP — s=start h=halt r=reset\n");
        break;
    default:
        printf("UNKNOWN (ignored)\n");
        break;
    }
}

int main(void)
{
    handle_command('s');
    handle_command('h');
    handle_command('r');
    handle_command('x');
    return 0;
}
