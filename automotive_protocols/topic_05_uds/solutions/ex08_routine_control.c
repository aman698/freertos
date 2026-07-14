/*
 * ex08_routine_control.c - Simulate RoutineControl (0x31) start/stop/requestResults.
 * Key concept: routine identifier plus sub-function drives a small routine state machine.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_ROUTINE_CONTROL 0x31U
#define SUB_START_ROUTINE 0x01U
#define SUB_STOP_ROUTINE 0x02U
#define SUB_REQUEST_RESULTS 0x03U
#define NRC_REQUEST_SEQUENCE_ERROR 0x24U

#define ROUTINE_INJECTOR_TEST 0x0203U

typedef enum {
    ROUTINE_IDLE = 0U,
    ROUTINE_RUNNING,
    ROUTINE_COMPLETE
} RoutineState_t;

static void handle_routine_control(RoutineState_t *state, uint8_t sub_function, uint16_t routine_id)
{
    if (state == NULL) {
        return;
    }

    printf("Request : 0x%02X 0x%02X 0x%02X 0x%02X\n",
           SID_ROUTINE_CONTROL, sub_function,
           (uint8_t)(routine_id >> 8), (uint8_t)(routine_id & 0xFFU));

    switch (sub_function) {
        case SUB_START_ROUTINE:
            *state = ROUTINE_RUNNING;
            printf("Response: 0x%02X 0x%02X 0x%02X 0x%02X status=0x01 (routine started)\n",
                   SID_ROUTINE_CONTROL + 0x40U, sub_function,
                   (uint8_t)(routine_id >> 8), (uint8_t)(routine_id & 0xFFU));
            break;

        case SUB_STOP_ROUTINE:
            if (*state == ROUTINE_IDLE) {
                printf("Response: 0x7F 0x%02X 0x%02X (requestSequenceError - not running)\n",
                       SID_ROUTINE_CONTROL, NRC_REQUEST_SEQUENCE_ERROR);
            } else {
                *state = ROUTINE_COMPLETE;
                printf("Response: 0x%02X 0x%02X 0x%02X 0x%02X status=0x00 (routine stopped)\n",
                       SID_ROUTINE_CONTROL + 0x40U, sub_function,
                       (uint8_t)(routine_id >> 8), (uint8_t)(routine_id & 0xFFU));
            }
            break;

        case SUB_REQUEST_RESULTS:
            {
                uint8_t status = (*state == ROUTINE_COMPLETE) ? 0x02U : 0x01U;
                printf("Response: 0x%02X 0x%02X 0x%02X 0x%02X status=0x%02X (%s)\n",
                       SID_ROUTINE_CONTROL + 0x40U, sub_function,
                       (uint8_t)(routine_id >> 8), (uint8_t)(routine_id & 0xFFU),
                       status, (status == 0x02U) ? "results ready" : "still running");
            }
            break;

        default:
            printf("Response: 0x7F 0x%02X 0x12 (subFunctionNotSupported)\n", SID_ROUTINE_CONTROL);
            break;
    }
}

int main(void)
{
    RoutineState_t injector_test = ROUTINE_IDLE;

    handle_routine_control(&injector_test, SUB_START_ROUTINE, ROUTINE_INJECTOR_TEST);
    handle_routine_control(&injector_test, SUB_REQUEST_RESULTS, ROUTINE_INJECTOR_TEST);
    handle_routine_control(&injector_test, SUB_STOP_ROUTINE, ROUTINE_INJECTOR_TEST);
    handle_routine_control(&injector_test, SUB_REQUEST_RESULTS, ROUTINE_INJECTOR_TEST);

    return 0;
}
