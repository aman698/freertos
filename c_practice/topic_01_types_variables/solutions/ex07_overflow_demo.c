/*
 * ex07_overflow_demo.c — uint8_t addition overflow
 * Key concept: result wraps; always check range before storing narrow type.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t adc_sum = 0;
    uint8_t sample_a = 200; /* two high ADC readings */
    uint8_t sample_b = 100;

    adc_sum = sample_a + sample_b; /* 300 mod 256 = 44 */

    printf("sample_a = %u\n", sample_a);
    printf("sample_b = %u\n", sample_b);
    printf("sum as uint8_t = %u (expected 44, NOT 300)\n", adc_sum);

    /* Safer: promote to wider type before add */
    uint16_t safe_sum = (uint16_t)sample_a + (uint16_t)sample_b;
    printf("sum as uint16_t = %u (correct)\n", safe_sum);

    return 0;
}
