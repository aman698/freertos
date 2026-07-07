/*
 * ex01_if_threshold.c — ADC high-limit alarm with if
 * Key concept: if compares sensor reading to a fixed threshold.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const uint16_t adc_raw = 3800U;       /* Simulated 12-bit ADC (0-4095) */
    const uint16_t high_limit = 3500U;  /* STM32: compare against trip point */

    printf("ADC raw = %u\n", adc_raw);

    if (adc_raw > high_limit) {
        printf("ALARM: over limit (%u > %u)\n", adc_raw, high_limit);
    }

    return 0;
}
