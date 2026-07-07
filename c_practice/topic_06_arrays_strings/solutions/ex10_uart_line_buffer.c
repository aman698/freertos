/**
 * Topic 06 - Exercise 10: UART line buffer simulation
 * STM32 context: ISR feeds bytes; main parses complete line
 * Build: gcc ex10_uart_line_buffer.c -o ex10 && ./ex10
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LINE_MAX 32U

typedef struct {
    char buf[LINE_MAX];
    size_t len;
    uint8_t ready;
} UartLineBuf_t;

static void uart_feed_byte(UartLineBuf_t *lb, char c)
{
    if (lb->ready) {
        return;
    }

    if (c == '\r' || c == '\n') {
        if (lb->len > 0U) {
            lb->buf[lb->len] = '\0';
            lb->ready = 1U;
        }
        return;
    }

    if (lb->len < LINE_MAX - 1U) {
        lb->buf[lb->len++] = c;
    }
}

int main(void)
{
    UartLineBuf_t line = { 0 };
    const char *sim_rx = "GET TEMP\r\n";

    for (size_t i = 0U; sim_rx[i] != '\0'; i++) {
        uart_feed_byte(&line, sim_rx[i]);
    }

    if (line.ready) {
        printf("Complete line: \"%s\" (len=%zu)\n", line.buf, line.len);
    }
    return 0;
}
