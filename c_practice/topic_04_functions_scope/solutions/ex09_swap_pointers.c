/*
 * ex09_swap_pointers.c — Swap two values using pointers
 * Key concept: pointers let function modify multiple caller variables.
 */
#include <stdint.h>
#include <stdio.h>

static void swap_u16(uint16_t *a, uint16_t *b)
{
    uint16_t temp = *a;
    *a = *b;
    *b = temp;
}

int main(void)
{
    uint16_t x = 100U;
    uint16_t y = 200U;

    printf("Before: x=%u y=%u\n", x, y);
    swap_u16(&x, &y);
    printf("After:  x=%u y=%u\n", x, y);

    return 0;
}
