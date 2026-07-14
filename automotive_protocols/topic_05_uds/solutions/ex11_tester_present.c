/*
 * ex11_tester_present.c - Simulate an S3 session timer kept alive by TesterPresent (0x3E).
 * Key concept: periodic TesterPresent requests reset the timer before it expires.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_TESTER_PRESENT 0x3EU
#define SUB_ZERO_SUB_FUNCTION 0x00U
#define S3_TIMEOUT_TICKS 5U

typedef struct {
    uint8_t ticks_since_last_request;
    uint8_t session_active;
} SessionTimer_t;

static void reset_timer(SessionTimer_t *timer)
{
    if (timer == NULL) {
        return;
    }
    timer->ticks_since_last_request = 0U;
    timer->session_active = 1U;
}

static void tick(SessionTimer_t *timer, uint8_t tester_present_sent)
{
    if (timer == NULL) {
        return;
    }
    if (timer->session_active == 0U) {
        printf("  session already timed out (in default session)\n");
        return;
    }

    if (tester_present_sent != 0U) {
        printf("  Request : 0x%02X 0x%02X\n", SID_TESTER_PRESENT, SUB_ZERO_SUB_FUNCTION);
        printf("  Response: 0x%02X 0x%02X (positive - timer reset)\n",
               SID_TESTER_PRESENT + 0x40U, SUB_ZERO_SUB_FUNCTION);
        timer->ticks_since_last_request = 0U;
        return;
    }

    timer->ticks_since_last_request++;
    if (timer->ticks_since_last_request >= S3_TIMEOUT_TICKS) {
        timer->session_active = 0U;
        printf("  S3 timeout reached -> session reverted to default session\n");
    } else {
        printf("  idle tick, %u/%u ticks since last TesterPresent\n",
               (unsigned)timer->ticks_since_last_request, (unsigned)S3_TIMEOUT_TICKS);
    }
}

int main(void)
{
    SessionTimer_t timer;
    reset_timer(&timer);

    /* index 3 sends TesterPresent before the S3 timeout would otherwise expire. */
    uint8_t keep_alive_at_tick3[] = {0U, 0U, 0U, 1U, 0U, 0U, 0U, 0U};
    size_t len1 = sizeof(keep_alive_at_tick3) / sizeof(keep_alive_at_tick3[0]);

    printf("-- session kept alive with periodic TesterPresent --\n");
    for (size_t i = 0U; i < len1; i++) {
        printf("Tick %2u:\n", (unsigned)i);
        tick(&timer, keep_alive_at_tick3[i]);
    }

    printf("-- session with no TesterPresent at all --\n");
    reset_timer(&timer);
    for (size_t i = 0U; i < 8U; i++) {
        printf("Tick %2u:\n", (unsigned)i);
        tick(&timer, 0U);
    }

    return 0;
}
