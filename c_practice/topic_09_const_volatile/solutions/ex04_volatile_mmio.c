/*
 * ex04_volatile_mmio.c — Simulated memory-mapped I/O access
 * Key concept: MMIO variables must be volatile — hardware changes them.
 */
#include <stdint.h>
#include <stdio.h>

static volatile uint32_t fake_gpio_odr = 0U;

int main(void)
{
    fake_gpio_odr = 0x00000020UL;  /* Set bit 5 */
    printf("GPIO ODR read back: 0x%08lX\n", (unsigned long)fake_gpio_odr);

    fake_gpio_odr |= 0x01UL;
    printf("After OR: 0x%08lX\n", (unsigned long)fake_gpio_odr);
    return 0;
}
