/*
 * ex11_multibit_field.c — Read and write 3-bit mode field
 * Key concept: multi-bit fields need wider mask than single bit.
 */
#include <stdint.h>
#include <stdio.h>

#define MODE_POS   4U
#define MODE_WIDTH 3U
#define MODE_MASK  ((1UL << MODE_WIDTH) - 1UL)

static uint32_t get_mode(uint32_t reg)
{
    return (reg >> MODE_POS) & MODE_MASK;
}

static uint32_t set_mode(uint32_t reg, uint32_t mode)
{
    reg &= ~(MODE_MASK << MODE_POS);
    reg |= (mode & MODE_MASK) << MODE_POS;
    return reg;
}

int main(void)
{
    uint32_t cr = 0U;
    cr = set_mode(cr, 5U);
    printf("CR=0x%08lX mode=%lu\n", (unsigned long)cr, (unsigned long)get_mode(cr));

    cr = set_mode(cr, 2U);
    printf("CR=0x%08lX mode=%lu (updated)\n", (unsigned long)cr, (unsigned long)get_mode(cr));
    return 0;
}
