/*
 * ex06_field_extract.c — Extract multi-bit field from register
 * Key concept: shift right then mask with (2^n - 1).
 */
#include <stdint.h>
#include <stdio.h>

#define FIELD_GET(reg, pos, width) \
    (((reg) >> (pos)) & ((1UL << (width)) - 1UL))

int main(void)
{
    uint32_t timer_cr1 = 0x00000084UL;  /* Bits 2:0 = 100 (divide by 16) */
    uint32_t psc_field = FIELD_GET(timer_cr1, 0U, 3U);

    printf("CR1 = 0x%08lX\n", (unsigned long)timer_cr1);
    printf("Prescaler field (3 bits @ pos 0) = %lu\n", (unsigned long)psc_field);
    return 0;
}
