/*
 * ex07_tester_present_keepalive.c - Simulate TesterPresent resetting the S3 timer.
 * Key concept: TesterPresent must arrive before S3 expires or the session is lost.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_TESTER_PRESENT 0x3EU
#define S3_TIMEOUT_TICKS   5U

typedef struct {
    uint8_t ticksRemaining;
    uint8_t sessionActive;
} S3Timer_t;

static void s3Init(S3Timer_t *timer)
{
    if (timer == NULL) {
        return;
    }
    timer->ticksRemaining = S3_TIMEOUT_TICKS;
    timer->sessionActive = 1U;
}

static void s3Tick(S3Timer_t *timer)
{
    if (timer == NULL) {
        return;
    }
    if (timer->sessionActive == 0U) {
        return;
    }
    if (timer->ticksRemaining > 0U) {
        timer->ticksRemaining--;
    }
    if (timer->ticksRemaining == 0U) {
        timer->sessionActive = 0U;
    }
}

static void s3Reset(S3Timer_t *timer)
{
    if (timer == NULL) {
        return;
    }
    if (timer->sessionActive != 0U) {
        timer->ticksRemaining = S3_TIMEOUT_TICKS;
    }
}

static void runLoop(uint8_t sendTesterPresentEvery, uint8_t totalTicks)
{
    S3Timer_t timer;

    s3Init(&timer);

    for (uint8_t tick = 1U; tick <= totalTicks; tick++) {
        if (timer.sessionActive == 0U) {
            printf("tick %u: session lost (S3 expired) - flow must restart from extended session\n", tick);
            break;
        }

        printf("tick %u: TransferData block sent, S3 ticks left = %u\n", tick, timer.ticksRemaining);

        if ((sendTesterPresentEvery != 0U) && ((tick % sendTesterPresentEvery) == 0U)) {
            printf("tick %u: TX 0x%02X 80 (TesterPresent, suppressPosRsp) -> S3 reset\n",
                   tick, SID_TESTER_PRESENT);
            s3Reset(&timer);
        }

        s3Tick(&timer);
    }

    if (timer.sessionActive != 0U) {
        printf("Loop finished with session still alive\n");
    }
}

int main(void)
{
    printf("-- With periodic TesterPresent --\n");
    runLoop(3U, 10U);

    printf("\n-- Without TesterPresent --\n");
    runLoop(0U, 10U);

    return 0;
}
