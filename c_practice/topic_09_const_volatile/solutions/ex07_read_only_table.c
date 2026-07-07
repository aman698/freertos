/*
 * ex07_read_only_table.c — const lookup table stored in flash
 * Key concept: const arrays often placed in ROM — no RAM cost.
 */
#include <stdint.h>
#include <stdio.h>

static const uint16_t sin_lut_q15[] = {
    0, 804, 1608, 2410, 3212, 4011, 4808, 5602
};

int main(void)
{
    for (uint8_t i = 0U; i < 8U; i++) {
        printf("lut[%u] = %u\n", i, sin_lut_q15[i]);
    }
    return 0;
}
