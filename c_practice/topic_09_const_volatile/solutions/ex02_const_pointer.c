/*
 * ex02_const_pointer.c — Pointer to const data is read-only
 * Key concept: const uint8_t* p prevents modifying *p through p.
 */
#include <stdint.h>
#include <stdio.h>

static uint8_t lookup(const uint8_t *table, uint8_t index)
{
    return table[index];
}

int main(void)
{
    const uint8_t adc_to_mv[] = { 0, 100, 200, 300, 400 };

    printf("LUT[3] = %u mV\n", lookup(adc_to_mv, 3U));
    return 0;
}
