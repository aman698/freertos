/*
 * ex11_inline_helper.c — Static inline helper for hot-path bit ops
 * Key concept: static inline suggests inlining for small GPIO helpers.
 */
#include <stdint.h>
#include <stdio.h>

static inline uint32_t bit_set(uint32_t reg, uint8_t bit)
{
    return reg | (1UL << bit);
}

static inline uint32_t bit_clear(uint32_t reg, uint8_t bit)
{
    return reg & ~(1UL << bit);
}

int main(void)
{
    uint32_t odr = 0x00000000UL;

    odr = bit_set(odr, 5U);    /* PA5 LD2 on */
    printf("ODR after set bit 5: 0x%08lX\n", (unsigned long)odr);

    odr = bit_clear(odr, 5U);
    printf("ODR after clear bit 5: 0x%08lX\n", (unsigned long)odr);

    return 0;
}
