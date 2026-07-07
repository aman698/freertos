/*
 * ex02_function_macro.c — Function-like macros with parenthesized args
 * Key concept: macro args must be parenthesized to avoid precedence bugs.
 */
#include <stdint.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main(void)
{
    uint16_t adc = 3500U;
    uint16_t lo = MIN(adc, 4095U);
    uint16_t hi = MAX(adc, 100U);

    printf("adc=%u clamped lo=%u hi=%u\n", adc, lo, hi);
    return 0;
}
