/*
 * ex08_continue_filter.c — Skip invalid ADC readings
 * Key concept: continue skips rest of loop body for bad samples.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const uint16_t samples[] = { 100, 4095, 200, 0, 300, 5000, 250 };
    const size_t count = sizeof(samples) / sizeof(samples[0]);
    const uint16_t min_valid = 50U;
    const uint16_t max_valid = 4000U;
    uint32_t sum = 0U;
    uint32_t valid_count = 0U;

    for (size_t i = 0U; i < count; i++) {
        if (samples[i] < min_valid || samples[i] > max_valid) {
            printf("  [%zu]=%u SKIPPED (out of range)\n", i, samples[i]);
            continue;
        }
        sum += samples[i];
        valid_count++;
        printf("  [%zu]=%u accepted\n", i, samples[i]);
    }

    if (valid_count > 0U) {
        printf("Valid average = %lu (%lu samples)\n",
               (unsigned long)(sum / valid_count), (unsigned long)valid_count);
    }

    return 0;
}
