/*
 * ex10_timer_callback.c - Timer module calls user callback on expiry.
 * Key concept: callbacks decouple driver and application logic.
 */
#include <stdio.h>

typedef void (*TimerCallback_t)(unsigned tick);

static void timer_run(unsigned period, TimerCallback_t cb)
{
    for (unsigned tick = 1U; tick <= 5U; tick++) {
        if ((tick % period) == 0U && cb != NULL) {
            cb(tick);
        }
    }
}

static void blink(unsigned tick)
{
    printf("blink at tick %u\n", tick);
}

int main(void)
{
    timer_run(2U, blink);
    return 0;
}
