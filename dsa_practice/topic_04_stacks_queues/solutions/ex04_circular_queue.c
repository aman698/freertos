/* Circular queue with head/tail/count. */
#include <stdbool.h>
#include <stdio.h>

#define CAP 3
typedef struct { int a[CAP]; int head, tail, count; } Queue;

static bool enq(Queue *q, int v) { if (q->count == CAP) return false; q->a[q->tail] = v; q->tail = (q->tail + 1) % CAP; q->count++; return true; }
static bool deq(Queue *q, int *v) { if (q->count == 0) return false; *v = q->a[q->head]; q->head = (q->head + 1) % CAP; q->count--; return true; }

int main(void)
{
    Queue q = {{0}, 0, 0, 0};
    int v;
    enq(&q, 1); enq(&q, 2); deq(&q, &v); enq(&q, 3);
    do { printf("%d ", v); } while (deq(&q, &v));
    putchar('\n');
    return 0;
}
