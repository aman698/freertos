/*
 * ex03_callback_parameter.c - Pass a callback into a function.
 * Key concept: library code can notify user code.
 */
#include <stdio.h>

typedef void (*EventCallback_t)(int event_id);

static void emit_event(EventCallback_t cb)
{
    if (cb != NULL) {
        cb(42);
    }
}

static void app_event_handler(int event_id)
{
    printf("event %d received\n", event_id);
}

int main(void)
{
    emit_event(app_event_handler);
    return 0;
}
