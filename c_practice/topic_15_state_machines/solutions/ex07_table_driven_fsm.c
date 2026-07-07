/*
 * ex07_table_driven_fsm.c - Transition table instead of nested logic.
 * Key concept: data can describe FSM transitions.
 */
#include <stdio.h>

typedef enum { ST_IDLE, ST_ARMED, ST_ALARM } State_t;
typedef enum { EV_ARM, EV_TRIGGER, EV_RESET } Event_t;

typedef struct {
    State_t from;
    Event_t event;
    State_t to;
} Transition_t;

static State_t dispatch(State_t state, Event_t event)
{
    const Transition_t table[] = {
        {ST_IDLE, EV_ARM, ST_ARMED},
        {ST_ARMED, EV_TRIGGER, ST_ALARM},
        {ST_ALARM, EV_RESET, ST_IDLE}
    };

    for (size_t i = 0U; i < sizeof(table) / sizeof(table[0]); i++) {
        if (table[i].from == state && table[i].event == event) {
            return table[i].to;
        }
    }
    return state;
}

int main(void)
{
    State_t state = ST_IDLE;
    Event_t events[] = {EV_ARM, EV_TRIGGER, EV_RESET};
    const char *names[] = {"IDLE", "ARMED", "ALARM"};
    for (size_t i = 0U; i < sizeof(events) / sizeof(events[0]); i++) {
        state = dispatch(state, events[i]);
        puts(names[state]);
    }
    return 0;
}
