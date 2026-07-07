/*
 * ex09_gpio_shadow_init.c — Initialize shadow registers for GPIO
 * Key concept: initialize all variables; firmware often mirrors hardware state.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Shadow copies of STM32-style GPIO registers (simulated on PC) */
    uint32_t moder_shadow = 0x00000000UL; /* all pins input mode */
    uint16_t odr_shadow   = 0x0000U;      /* all outputs low */
    uint16_t pin_mask     = (1U << 5);    /* PB5 = LED on NUCLEO */

    printf("After reset init:\n");
    printf("  MODER shadow = 0x%08lX\n", (unsigned long)moder_shadow);
    printf("  ODR shadow   = 0x%04X\n", odr_shadow);

    /* Configure PB5 as output and set high */
    odr_shadow |= pin_mask;
    printf("\nLED ON: ODR shadow = 0x%04X\n", odr_shadow);

    odr_shadow &= (uint16_t)~pin_mask;
    printf("LED OFF: ODR shadow = 0x%04X\n", odr_shadow);

    return 0;
}
