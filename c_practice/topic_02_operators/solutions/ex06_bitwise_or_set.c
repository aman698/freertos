/*
 * ex06_bitwise_or_set.c — Set LED bit with OR
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t odr = 0x0000U;
    const uint32_t led_mask = (1U << 5);

    odr |= led_mask;
    printf("ODR after set: 0x%04lX\n", (unsigned long)odr);
    return 0;
}
