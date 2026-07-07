/*
 * ex12_uart_rx_ring.c - Simulate UART RX bytes collected in a ring buffer.
 * Key concept: ISR pushes bytes, main code drains them.
 */
#include <stdbool.h>
#include <stdio.h>

#define CAP 8U

typedef struct {
    char data[CAP];
    size_t head;
    size_t tail;
    size_t count;
} Ring_t;

static bool push(Ring_t *r, char ch)
{
    if (r->count == CAP) {
        return false;
    }
    r->data[r->tail] = ch;
    r->tail = (r->tail + 1U) % CAP;
    r->count++;
    return true;
}

static bool pop(Ring_t *r, char *ch)
{
    if (r->count == 0U) {
        return false;
    }
    *ch = r->data[r->head];
    r->head = (r->head + 1U) % CAP;
    r->count--;
    return true;
}

int main(void)
{
    Ring_t rx = {{0}, 0U, 0U, 0U};
    const char *incoming = "OK\n";
    char ch;
    for (size_t i = 0U; incoming[i] != '\0'; i++) {
        push(&rx, incoming[i]);
    }
    while (pop(&rx, &ch)) {
        putchar(ch);
    }
    return 0;
}
