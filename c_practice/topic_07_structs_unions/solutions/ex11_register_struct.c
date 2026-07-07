/*
 * ex11_register_struct.c — GPIO register block as struct
 * Key concept: struct overlay maps peripheral register addresses.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile uint32_t moder;
    volatile uint32_t otyper;
    volatile uint32_t ospeedr;
    volatile uint32_t pupdr;
    volatile uint32_t idr;
    volatile uint32_t odr;
} gpio_bank_t;

int main(void)
{
    gpio_bank_t gpio = { 0 };
    gpio.moder = 0x00000001UL;  /* PA0 output */
    gpio.odr = (1UL << 5);      /* PA5 high — LD2 */

    printf("GPIO moder=0x%08lX odr=0x%08lX\n",
           (unsigned long)gpio.moder, (unsigned long)gpio.odr);
    return 0;
}
