/*
 * ex04_motor_control.c - Motor controller states and events.
 * Key concept: events drive transitions.
 */
#include <stdio.h>

typedef enum { MOTOR_STOPPED, MOTOR_RUNNING, MOTOR_FAULT } MotorState_t;
typedef enum { EVT_START, EVT_STOP, EVT_FAULT, EVT_RESET } Event_t;

static MotorState_t handle(MotorState_t state, Event_t event)
{
    if (event == EVT_FAULT) {
        return MOTOR_FAULT;
    }
    if (state == MOTOR_STOPPED && event == EVT_START) {
        return MOTOR_RUNNING;
    }
    if (state == MOTOR_RUNNING && event == EVT_STOP) {
        return MOTOR_STOPPED;
    }
    if (state == MOTOR_FAULT && event == EVT_RESET) {
        return MOTOR_STOPPED;
    }
    return state;
}

int main(void)
{
    MotorState_t state = MOTOR_STOPPED;
    Event_t events[] = {EVT_START, EVT_FAULT, EVT_START, EVT_RESET};
    const char *names[] = {"STOPPED", "RUNNING", "FAULT"};

    for (size_t i = 0U; i < sizeof(events) / sizeof(events[0]); i++) {
        state = handle(state, events[i]);
        puts(names[state]);
    }
    return 0;
}
