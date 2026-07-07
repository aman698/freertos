/*
 * ex11_event_queue.c - Queue small event structures.
 * Key concept: event queues carry type plus data.
 */
#include <stdbool.h>
#include <stdio.h>

#define CAP 3U

typedef struct {
    unsigned type;
    unsigned data;
} Event_t;

typedef struct {
    Event_t items[CAP];
    size_t head;
    size_t tail;
    size_t count;
} EventQueue_t;

static bool post(EventQueue_t *q, Event_t event)
{
    if (q->count == CAP) {
        return false;
    }
    q->items[q->tail] = event;
    q->tail = (q->tail + 1U) % CAP;
    q->count++;
    return true;
}

static bool get(EventQueue_t *q, Event_t *event)
{
    if (q->count == 0U) {
        return false;
    }
    *event = q->items[q->head];
    q->head = (q->head + 1U) % CAP;
    q->count--;
    return true;
}

int main(void)
{
    EventQueue_t q = {{{0}}, 0U, 0U, 0U};
    Event_t event;
    post(&q, (Event_t){1U, 55U});
    post(&q, (Event_t){2U, 99U});
    while (get(&q, &event)) {
        printf("event type=%u data=%u\n", event.type, event.data);
    }
    return 0;
}
