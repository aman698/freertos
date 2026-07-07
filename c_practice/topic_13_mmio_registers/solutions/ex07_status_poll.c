/*
 * ex07_status_poll.c - Poll a status flag with a timeout.
 * Key concept: production polling should have an escape path.
 */
#include <stdint.h>
#include <stdio.h>

#define READY_FLAG (1UL << 1U)

int main(void)
{
    volatile uint32_t sr = 0U;
    for (unsigned tries = 0U; tries < 5U; tries++) {
        if (tries == 3U) {
            sr |= READY_FLAG;
        }
        if ((sr & READY_FLAG) != 0U) {
            printf("ready after %u polls\n", tries + 1U);
            break;
        }
    }
    return 0;
}
