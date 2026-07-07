/*
 * ex09_popcount.c — Count number of set bits (population count)
 * Key concept: loop and test each bit — used for diagnostics and Hamming weight.
 */
#include <stdint.h>
#include <stdio.h>

static uint8_t popcount32(uint32_t x)
{
    uint8_t count = 0U;
    while (x != 0U) {
        count += (uint8_t)(x & 1U);
        x >>= 1;
    }
    return count;
}

int main(void)
{
    uint32_t values[] = { 0U, 1U, 0xFFU, 0x80000001UL };

    for (size_t i = 0U; i < sizeof(values) / sizeof(values[0]); i++) {
        printf("0x%08lX has %u bits set\n",
               (unsigned long)values[i], popcount32(values[i]));
    }
    return 0;
}
