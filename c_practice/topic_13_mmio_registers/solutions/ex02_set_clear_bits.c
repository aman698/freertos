/*
 * ex02_set_clear_bits.c - Set and clear register bits.
 * Key concept: |= sets bits, &= ~mask clears bits.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

int main(void)
{
    uint32_t cr = 0U;
    cr |= BIT(0);
    cr |= BIT(3);
    cr &= ~BIT(0);

    printf("CR = 0x%08lX, bit3=%lu\n",
           (unsigned long)cr, (unsigned long)((cr & BIT(3)) != 0U));
    return 0;
}
