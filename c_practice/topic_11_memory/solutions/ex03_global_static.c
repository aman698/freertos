/*
 * ex03_global_static.c - File-scope static data models private driver state.
 * Key concept: global lifetime with internal linkage.
 */
#include <stdbool.h>
#include <stdio.h>

static bool g_uart_ready = false;
static unsigned g_baud = 0U;

static void uart_init(unsigned baud)
{
    g_baud = baud;
    g_uart_ready = true;
}

int main(void)
{
    printf("ready before init = %s\n", g_uart_ready ? "yes" : "no");
    uart_init(115200U);
    printf("ready after init = %s, baud = %u\n", g_uart_ready ? "yes" : "no", g_baud);
    return 0;
}
