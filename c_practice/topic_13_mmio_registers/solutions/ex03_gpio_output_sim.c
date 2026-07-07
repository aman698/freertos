/*
 * ex03_gpio_output_sim.c - Simulate GPIO output register writes.
 * Key concept: one output pin is one bit in ODR.
 */
#include <stdint.h>
#include <stdio.h>

#define LED_PIN 5U
#define BIT(n)  (1UL << (n))

int main(void)
{
    uint32_t odr = 0U;
    odr |= BIT(LED_PIN);
    printf("LED on  ODR=0x%08lX\n", (unsigned long)odr);
    odr &= ~BIT(LED_PIN);
    printf("LED off ODR=0x%08lX\n", (unsigned long)odr);
    return 0;
}
