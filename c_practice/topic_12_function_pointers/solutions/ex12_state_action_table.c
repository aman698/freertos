/*
 * ex12_state_action_table.c - State entry actions stored in a table.
 * Key concept: FSMs often use action function tables.
 */
#include <stdio.h>

typedef enum {
    STATE_IDLE,
    STATE_RUN,
    STATE_FAULT,
    STATE_COUNT
} State_t;

typedef void (*Action_t)(void);

static void enter_idle(void)  { puts("enter idle"); }
static void enter_run(void)   { puts("enter run"); }
static void enter_fault(void) { puts("enter fault"); }

int main(void)
{
    Action_t on_enter[STATE_COUNT] = {enter_idle, enter_run, enter_fault};
    State_t sequence[] = {STATE_IDLE, STATE_RUN, STATE_FAULT};

    for (size_t i = 0U; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
        on_enter[sequence[i]]();
    }
    return 0;
}
