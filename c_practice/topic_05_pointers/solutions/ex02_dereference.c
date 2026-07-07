/*
 * ex02_dereference.c — Read and write through pointer
 * Key concept: *ptr accesses the object at the address held by ptr.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint16_t gpio_odr = 0x0000U;
    uint16_t *odr_ptr = &gpio_odr;

    printf("Before: ODR = 0x%04X\n", gpio_odr);

    *odr_ptr |= (1U << 5);  /* Set PA5 via pointer — LD2 on STM32 */

    printf("After:  ODR = 0x%04X\n", gpio_odr);
    return 0;
}
