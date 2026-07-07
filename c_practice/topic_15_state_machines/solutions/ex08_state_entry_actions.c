/*
 * ex08_state_entry_actions.c - Run an action when entering each state.
 * Key concept: separate transition decision from side effects.
 */
#include <stdio.h>

typedef enum { ST_SLEEP, ST_SAMPLE, ST_SEND, ST_COUNT } State_t;
typedef void (*Action_t)(void);

static void enter_sleep(void)  { puts("sleep"); }
static void enter_sample(void) { puts("sample sensor"); }
static void enter_send(void)   { puts("send data"); }

int main(void)
{
    Action_t entry[ST_COUNT] = {enter_sleep, enter_sample, enter_send};
    State_t sequence[] = {ST_SLEEP, ST_SAMPLE, ST_SEND};
    for (size_t i = 0U; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
        entry[sequence[i]]();
    }
    return 0;
}
