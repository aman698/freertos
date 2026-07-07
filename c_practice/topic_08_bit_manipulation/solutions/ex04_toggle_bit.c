/*
 * ex04_toggle_bit.c — Toggle bit with XOR
 * Key concept: reg ^= BIT(n) flips bit n — common for LED blink.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

int main(void)
{
    uint32_t gpio_odr = 0x00000000UL;

    gpio_odr ^= BIT(5);
    printf("After toggle 1: 0x%08lX\n", (unsigned long)gpio_odr);

    gpio_odr ^= BIT(5);
    printf("After toggle 2: 0x%08lX\n", (unsigned long)gpio_odr);

    return 0;
}
