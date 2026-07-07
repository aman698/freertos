/*
 * ex10_brr_set_reset.c - Simulate atomic GPIO set/reset behavior.
 * Key concept: BSRR sets and resets pins without read-modify-write.
 */
#include <stdint.h>
#include <stdio.h>

#define PIN 5U
#define BIT(n) (1UL << (n))

static void write_bsrr(uint32_t *odr, uint32_t value)
{
    *odr |= (value & 0xFFFFUL);
    *odr &= ~(value >> 16U);
}

int main(void)
{
    uint32_t odr = 0U;
    write_bsrr(&odr, BIT(PIN));
    printf("set   ODR=0x%08lX\n", (unsigned long)odr);
    write_bsrr(&odr, BIT(PIN) << 16U);
    printf("reset ODR=0x%08lX\n", (unsigned long)odr);
    return 0;
}
