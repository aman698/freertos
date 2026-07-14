/*
 * ex05_security_access_lockout.c - Simulate SecurityAccess wrong-key lockout.
 * Key concept: too many bad keys triggers exceedNumberOfAttempts, then a delay NRC.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_SECURITY_ACCESS 0x27U
#define NRC_EXCEED_NUMBER_OF_ATTEMPTS 0x36U
#define NRC_REQUIRED_TIME_DELAY_NOT_EXPIRED 0x37U
#define MAX_ATTEMPTS 3U
#define LOCKOUT_TICKS 5U

typedef struct {
    uint8_t attempt_count;
    uint8_t locked;
    uint8_t lockout_ticks_left;
} SecurityState_t;

static void reset_state(SecurityState_t *state)
{
    if (state == NULL) {
        return;
    }
    state->attempt_count = 0U;
    state->locked = 0U;
    state->lockout_ticks_left = 0U;
}

/* key_ok = 0 simulates a wrong key on this tick. */
static void try_send_key(SecurityState_t *state, uint8_t key_ok)
{
    if (state == NULL) {
        return;
    }

    if (state->locked != 0U) {
        if (state->lockout_ticks_left > 0U) {
            state->lockout_ticks_left--;
        }
        if (state->lockout_ticks_left == 0U) {
            state->locked = 0U;
            state->attempt_count = 0U;
            printf("Delay elapsed  -> lockout cleared\n");
        } else {
            printf("Response: 0x7F 0x%02X 0x%02X (requiredTimeDelayNotExpired, %u ticks left)\n",
                   SID_SECURITY_ACCESS, NRC_REQUIRED_TIME_DELAY_NOT_EXPIRED,
                   (unsigned)state->lockout_ticks_left);
        }
        return;
    }

    if (key_ok != 0U) {
        state->attempt_count = 0U;
        printf("Response: 0x%02X (positive - security access granted)\n",
               SID_SECURITY_ACCESS + 0x40U);
        return;
    }

    state->attempt_count++;
    if (state->attempt_count >= MAX_ATTEMPTS) {
        state->locked = 1U;
        state->lockout_ticks_left = LOCKOUT_TICKS;
        printf("Response: 0x7F 0x%02X 0x%02X (exceedNumberOfAttempts, locked for %u ticks)\n",
               SID_SECURITY_ACCESS, NRC_EXCEED_NUMBER_OF_ATTEMPTS, (unsigned)LOCKOUT_TICKS);
    } else {
        printf("Response: 0x7F 0x%02X 0x35 (invalidKey, attempt %u/%u)\n",
               SID_SECURITY_ACCESS, (unsigned)state->attempt_count, (unsigned)MAX_ATTEMPTS);
    }
}

int main(void)
{
    SecurityState_t state;
    reset_state(&state);

    uint8_t sequence[] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U};
    size_t sequence_len = sizeof(sequence) / sizeof(sequence[0]);

    for (size_t i = 0U; i < sequence_len; i++) {
        printf("Tick %2u: ", (unsigned)i);
        try_send_key(&state, sequence[i]);
    }

    return 0;
}
