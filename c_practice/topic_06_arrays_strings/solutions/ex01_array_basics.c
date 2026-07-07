/**
 * Topic 06 - Exercise 01: One-dimensional array basics
 * STM32 context: ADC sample buffer averaging
 * Build: gcc ex01_array_basics.c -o ex01 && ./ex01
 */
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t adc_samples[] = { 120, 118, 122, 119, 121, 120, 118, 122 };
    const size_t count = sizeof(adc_samples) / sizeof(adc_samples[0]);
    uint32_t sum = 0U;

    printf("ADC buffer (%zu samples):\n", count);
    for (size_t i = 0U; i < count; i++) {
        printf("  [%zu] = %u\n", i, adc_samples[i]);
        sum += adc_samples[i];
    }

    uint8_t average = (uint8_t)(sum / count);
    printf("Sum=%lu  Average=%u (0-255 scale)\n", (unsigned long)sum, average);
    return 0;
}
