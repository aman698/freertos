/*
 * ex09_timeout_state.c - Leave a waiting state on timeout.
 * Key concept: timers are events too.
 */
#include <stdio.h>

typedef enum { ST_SEND_REQ, ST_WAIT_ACK, ST_TIMEOUT } State_t;

int main(void)
{
    State_t state = ST_SEND_REQ;
    unsigned elapsed = 0U;

    puts("send request");
    state = ST_WAIT_ACK;
    while (state == ST_WAIT_ACK) {
        elapsed++;
        if (elapsed >= 3U) {
            state = ST_TIMEOUT;
        }
    }
    printf("timeout after %u ticks\n", elapsed);
    return 0;
}
