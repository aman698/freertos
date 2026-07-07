/*
 * ex12_embedded_expr.c — Combined mask/shift/compare expression
 */
#include <stdint.h>
#include <stdio.h>

#define MODE_POS   4U
#define MODE_MASK  (0x3U << MODE_POS)

int main(void)
{
    uint32_t cr = 0x00000030U;  /* mode field = 3 at bits 4-5 */
    uint32_t mode = (cr & MODE_MASK) >> MODE_POS;

    printf("CR=0x%08lX mode=%lu\n", (unsigned long)cr, (unsigned long)mode);
    return 0;
}
