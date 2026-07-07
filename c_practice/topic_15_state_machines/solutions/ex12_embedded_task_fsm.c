/*
 * ex12_embedded_task_fsm.c - Sensor task lifecycle.
 * Key concept: RTOS tasks often run one FSM step per loop.
 */
#include <stdio.h>

typedef enum { TASK_INIT, TASK_READ, TASK_SEND, TASK_SLEEP } TaskState_t;

int main(void)
{
    TaskState_t state = TASK_INIT;
    for (unsigned step = 0U; step < 6U; step++) {
        switch (state) {
        case TASK_INIT:
            puts("init sensor");
            state = TASK_READ;
            break;
        case TASK_READ:
            puts("read sensor");
            state = TASK_SEND;
            break;
        case TASK_SEND:
            puts("send sample");
            state = TASK_SLEEP;
            break;
        case TASK_SLEEP:
            puts("sleep until next period");
            state = TASK_READ;
            break;
        }
    }
    return 0;
}
