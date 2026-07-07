/*
 * ex04_for_sum.c — Average ADC buffer with for loop
 * Key concept: for iterates a known count over a sample array.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const uint16_t samples[] = { 2100, 2120, 2110, 2095, 2105, 2115, 2108, 2112 };
    const size_t count = sizeof(samples) / sizeof(samples[0]);
    uint32_t sum = 0U;

    printf("Samples (%zu):\n", count);
    for (size_t i = 0U; i < count; i++) {
        printf("  [%zu] = %u\n", i, samples[i]);
        sum += samples[i];
    }

    uint16_t average = (uint16_t)(sum / count);
    printf("Sum=%lu  Average=%u\n", (unsigned long)sum, average);
    return 0;
}
