/*
 * ex05_ring_buffer_bytes.c - Byte ring buffer.
 * Key concept: head/tail wrap around fixed storage.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define RB_CAP 4U

typedef struct {
    uint8_t data[RB_CAP];
    size_t head;
    size_t tail;
    size_t count;
} Ring_t;

static bool rb_push(Ring_t *rb, uint8_t byte)
{
    if (rb->count == RB_CAP) {
        return false;
    }
    rb->data[rb->tail] = byte;
    rb->tail = (rb->tail + 1U) % RB_CAP;
    rb->count++;
    return true;
}

static bool rb_pop(Ring_t *rb, uint8_t *byte)
{
    if (rb->count == 0U) {
        return false;
    }
    *byte = rb->data[rb->head];
    rb->head = (rb->head + 1U) % RB_CAP;
    rb->count--;
    return true;
}

int main(void)
{
    Ring_t rb = {{0}, 0U, 0U, 0U};
    uint8_t byte;
    rb_push(&rb, 'A');
    rb_push(&rb, 'B');
    while (rb_pop(&rb, &byte)) {
        putchar(byte);
    }
    putchar('\n');
    return 0;
}
