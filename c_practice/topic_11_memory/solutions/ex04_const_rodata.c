/*
 * ex04_const_rodata.c - Const tables are read-only program data.
 * Key concept: lookup tables usually belong in flash/rodata.
 */
#include <stdint.h>
#include <stdio.h>

static const uint16_t adc_to_mv[] = {0U, 805U, 1611U, 2416U, 3222U};

int main(void)
{
    for (size_t i = 0U; i < sizeof(adc_to_mv) / sizeof(adc_to_mv[0]); i++) {
        printf("step %zu = %u mV\n", i, adc_to_mv[i]);
    }
    return 0;
}
