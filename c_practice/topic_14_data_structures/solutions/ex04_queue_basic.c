/*
 * ex04_queue_basic.c - Fixed-size FIFO queue.
 * Key concept: queue pops in insertion order.
 */
#include <stdbool.h>
#include <stdio.h>

#define QUEUE_CAP 4U

typedef struct {
    int data[QUEUE_CAP];
    size_t head;
    size_t tail;
    size_t count;
} Queue_t;

static bool enqueue(Queue_t *q, int value)
{
    if (q->count == QUEUE_CAP) {
        return false;
    }
    q->data[q->tail] = value;
    q->tail = (q->tail + 1U) % QUEUE_CAP;
    q->count++;
    return true;
}

static bool dequeue(Queue_t *q, int *value)
{
    if (q->count == 0U) {
        return false;
    }
    *value = q->data[q->head];
    q->head = (q->head + 1U) % QUEUE_CAP;
    q->count--;
    return true;
}

int main(void)
{
    Queue_t q = {{0}, 0U, 0U, 0U};
    int value;
    enqueue(&q, 1);
    enqueue(&q, 2);
    while (dequeue(&q, &value)) {
        printf("%d\n", value);
    }
    return 0;
}
