/*
 * ex10_gpio_shadow.c — Shadow register before writing hardware
 * Key concept: maintain software copy of ODR; update HW from shadow.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

static uint32_t gpio_odr_shadow = 0U;

static void shadow_set_pin(uint8_t pin)
{
    gpio_odr_shadow |= BIT(pin);
}

static void shadow_clear_pin(uint8_t pin)
{
    gpio_odr_shadow &= ~BIT(pin);
}

static void write_odr_to_hw(void)
{
    printf("Write to GPIOA->ODR: 0x%08lX\n", (unsigned long)gpio_odr_shadow);
}

int main(void)
{
    shadow_set_pin(5U);
    shadow_set_pin(7U);
    shadow_clear_pin(7U);
    write_odr_to_hw();
    return 0;
}
