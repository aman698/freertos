/*
 * ex06_ring_buffer_full_empty.c - Detect full and empty states.
 * Key concept: fixed queues must reject overflow.
 */
#include <stdbool.h>
#include <stdio.h>

#define CAP 2U

typedef struct {
    int data[CAP];
    size_t tail;
    size_t count;
} TinyQueue_t;

static bool push(TinyQueue_t *q, int value)
{
    if (q->count == CAP) {
        return false;
    }
    q->data[q->tail] = value;
    q->tail = (q->tail + 1U) % CAP;
    q->count++;
    return true;
}

int main(void)
{
    TinyQueue_t q = {{0}, 0U, 0U};
    printf("push1=%s\n", push(&q, 1) ? "ok" : "full");
    printf("push2=%s\n", push(&q, 2) ? "ok" : "full");
    printf("push3=%s\n", push(&q, 3) ? "ok" : "full");
    return 0;
}
