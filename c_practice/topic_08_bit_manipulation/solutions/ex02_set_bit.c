/*
 * ex02_set_bit.c — Set one bit with OR mask
 * Key concept: reg |= BIT(n) sets bit n without affecting others.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

int main(void)
{
    uint32_t gpio_odr = 0x00000000UL;

    gpio_odr |= BIT(5);  /* PA5 LD2 on */
    printf("ODR after set bit 5: 0x%08lX\n", (unsigned long)gpio_odr);
    return 0;
}
