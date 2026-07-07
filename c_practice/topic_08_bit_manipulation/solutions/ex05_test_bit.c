/*
 * ex05_test_bit.c — Test if bit is set in IDR
 * Key concept: (reg & BIT(n)) != 0 checks pin state.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

int main(void)
{
    uint32_t gpio_idr = 0x00002000UL;  /* Bit 13 high — button released (pull-up) */
    uint8_t pin = 13U;

    if (gpio_idr & BIT(pin)) {
        printf("Pin %u: HIGH\n", pin);
    } else {
        printf("Pin %u: LOW\n", pin);
    }

    gpio_idr &= ~BIT(pin);  /* Simulate button press */
    if (gpio_idr & BIT(pin)) {
        printf("Pin %u: HIGH\n", pin);
    } else {
        printf("Pin %u: LOW (pressed)\n", pin);
    }

    return 0;
}
