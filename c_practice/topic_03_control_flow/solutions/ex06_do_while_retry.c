/*
 * ex06_do_while_retry.c — SPI transfer retry with do-while
 * Key concept: do-while runs body at least once before condition check.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

static bool spi_transfer_once(uint8_t attempt)
{
    /* Simulated: succeed on 3rd attempt */
    return (attempt >= 3U);
}

int main(void)
{
    uint8_t attempt = 0U;
    bool ok = false;

    do {
        attempt++;
        ok = spi_transfer_once(attempt);
        printf("SPI attempt %u: %s\n", attempt, ok ? "OK" : "FAIL");
    } while (!ok && attempt < 3U);

    if (ok) {
        printf("Transfer complete after %u attempt(s)\n", attempt);
    } else {
        printf("Transfer failed after max retries\n");
    }

    return 0;
}
