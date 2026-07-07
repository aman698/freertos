/*
 * ex11_bit_macro_header.c — BIT/SET_BIT/CLEAR_BIT macro pattern
 * Key concept: do-while(0) wraps multi-statement register macros safely.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n)       (1UL << (n))
#define SET_BIT(r, n)    do { (r) |= BIT(n); } while (0)
#define CLEAR_BIT(r, n)  do { (r) &= ~BIT(n); } while (0)

int main(void)
{
    uint32_t odr = 0UL;
    SET_BIT(odr, 5);
    SET_BIT(odr, 7);
    CLEAR_BIT(odr, 7);
    printf("ODR = 0x%08lX\n", (unsigned long)odr);
    return 0;
}
