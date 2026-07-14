/*
 * ex05_erase_routine_control.c - Simulate a RoutineControl (0x31) erase-memory routine.
 * Key concept: start a routine, then poll requestResults until it reports complete.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_ROUTINE_CONTROL       0x31U
#define SID_ROUTINE_CONTROL_RESP  0x71U
#define ROUTINE_SUBFUNC_START     0x01U
#define ROUTINE_SUBFUNC_RESULTS   0x03U
#define ROUTINE_ID_ERASE_MEMORY   0xFF00U

typedef enum {
    ROUTINE_IN_PROGRESS = 0,
    ROUTINE_COMPLETE    = 1
} RoutineStatus_t;

typedef struct {
    uint32_t startAddress;
    uint32_t length;
    uint8_t  pollsRemaining; /* simulated hardware erase latency */
} EraseSim_t;

static void startRoutine(EraseSim_t *sim, uint32_t address, uint32_t length, uint8_t latencyPolls)
{
    if (sim == NULL) {
        return;
    }

    sim->startAddress = address;
    sim->length = length;
    sim->pollsRemaining = latencyPolls;

    printf("TX: %02X %02X %04X (erase 0x%08lX..0x%08lX)\n",
           SID_ROUTINE_CONTROL, ROUTINE_SUBFUNC_START, ROUTINE_ID_ERASE_MEMORY,
           (unsigned long)address, (unsigned long)(address + length));
    printf("RX: %02X %02X %04X (routine started)\n",
           SID_ROUTINE_CONTROL_RESP, ROUTINE_SUBFUNC_START, ROUTINE_ID_ERASE_MEMORY);
}

static RoutineStatus_t pollRoutine(EraseSim_t *sim)
{
    if (sim == NULL) {
        return ROUTINE_COMPLETE;
    }

    if (sim->pollsRemaining > 0U) {
        sim->pollsRemaining--;
        return ROUTINE_IN_PROGRESS;
    }

    return ROUTINE_COMPLETE;
}

int main(void)
{
    EraseSim_t erase;
    RoutineStatus_t status;
    uint8_t pollCount = 0U;

    startRoutine(&erase, 0x08004000U, 0x00010000U, 3U);

    do {
        printf("TX: %02X %02X %04X (requestResults)\n",
               SID_ROUTINE_CONTROL, ROUTINE_SUBFUNC_RESULTS, ROUTINE_ID_ERASE_MEMORY);
        status = pollRoutine(&erase);
        pollCount++;

        if (status == ROUTINE_IN_PROGRESS) {
            printf("RX: %02X %02X %04X (in progress)\n",
                   SID_ROUTINE_CONTROL_RESP, ROUTINE_SUBFUNC_RESULTS, ROUTINE_ID_ERASE_MEMORY);
        } else {
            printf("RX: %02X %02X %04X (complete)\n",
                   SID_ROUTINE_CONTROL_RESP, ROUTINE_SUBFUNC_RESULTS, ROUTINE_ID_ERASE_MEMORY);
        }
    } while (status == ROUTINE_IN_PROGRESS);

    printf("Erase routine finished after %u poll(s)\n", pollCount);

    return 0;
}
