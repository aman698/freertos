/*
 * ex02_modulo_wrap.c — Circular buffer index with modulo
 * Key concept: index % capacity wraps without branches.
 */
#include <stdint.h>
#include <stdio.h>

#define BUF_SIZE 8

int main(void)
{
    uint32_t head = 6;

    printf("Ring buffer size: %d\n", BUF_SIZE);
    printf("Start head: %lu\n", (unsigned long)head);

    for (int i = 0; i < 5; i++) {
        head = (head + 1) % BUF_SIZE;
        printf("  push -> head = %lu\n", (unsigned long)head);
    }

    /* UART RX example: advance tail */
    uint32_t tail = 0;
    tail = (tail + 3) % BUF_SIZE;
    printf("tail after 3 bytes: %lu\n", (unsigned long)tail);

    return 0;
}
