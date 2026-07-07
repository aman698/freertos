/*
 * ex03_clear_bit.c — Clear one bit with AND NOT mask
 * Key concept: reg &= ~BIT(n) clears bit n, preserves others.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

int main(void)
{
    uint32_t gpio_odr = 0x000000FFUL;

    gpio_odr &= ~BIT(5);
    printf("ODR after clear bit 5: 0x%08lX\n", (unsigned long)gpio_odr);
    return 0;
}
