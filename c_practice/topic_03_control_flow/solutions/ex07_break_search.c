/*
 * ex07_break_search.c — Find first sample above limit
 * Key concept: break exits loop early when condition met.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const uint16_t samples[] = { 100, 150, 280, 320, 400 };
    const uint16_t limit = 300U;
    const size_t count = sizeof(samples) / sizeof(samples[0]);
    size_t found_idx = count;  /* count means not found */

    for (size_t i = 0U; i < count; i++) {
        if (samples[i] > limit) {
            found_idx = i;
            break;
        }
    }

    if (found_idx < count) {
        printf("First over-limit sample at index %zu: value=%u\n",
               found_idx, samples[found_idx]);
    } else {
        printf("No sample over limit %u\n", limit);
    }

    return 0;
}
