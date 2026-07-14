/*
 * ex06_check_programming_dependencies.c - Simulate a checkProgrammingDependencies routine.
 * Key concept: reprogramming is accepted only if checksum, coverage, and prerequisites all pass.
 */
#include <stdint.h>
#include <stdio.h>

#define NRC_GENERAL_PROGRAMMING_FAILURE 0x72U

typedef struct {
    uint8_t checksumOk;
    uint8_t allBlocksWritten;
    uint8_t prerequisitesMet;
} ProgrammingState_t;

static uint8_t checkProgrammingDependencies(const ProgrammingState_t *state, const char **reasonOut)
{
    if ((state == NULL) || (reasonOut == NULL)) {
        return 0U;
    }

    *reasonOut = "OK";

    if (state->checksumOk == 0U) {
        *reasonOut = "checksum mismatch";
        return 0U;
    }
    if (state->allBlocksWritten == 0U) {
        *reasonOut = "missing transfer blocks";
        return 0U;
    }
    if (state->prerequisitesMet == 0U) {
        *reasonOut = "unmet prerequisite (e.g. calibration not flashed)";
        return 0U;
    }

    return 1U;
}

static void report(const char *label, const ProgrammingState_t *state)
{
    const char *reason = NULL;

    if ((label == NULL) || (state == NULL)) {
        return;
    }

    if (checkProgrammingDependencies(state, &reason) != 0U) {
        printf("%s -> PASS (%s)\n", label, reason);
    } else {
        printf("%s -> FAIL, NRC 0x%02X: %s\n", label, NRC_GENERAL_PROGRAMMING_FAILURE, reason);
    }
}

int main(void)
{
    ProgrammingState_t good = {1U, 1U, 1U};
    ProgrammingState_t badChecksum = {0U, 1U, 1U};
    ProgrammingState_t badBlocks = {1U, 0U, 1U};
    ProgrammingState_t badPrereq = {1U, 1U, 0U};

    report("Case 1 (all good)", &good);
    report("Case 2 (checksum fail)", &badChecksum);
    report("Case 3 (blocks missing)", &badBlocks);
    report("Case 4 (prerequisite unmet)", &badPrereq);

    return 0;
}
