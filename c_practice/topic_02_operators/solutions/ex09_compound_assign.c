/*
 * ex09_compound_assign.c — &=, |=, ^= on shadow register
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t shadow = 0xFF00U;

    shadow |= (1U << 3);   /* set bit 3 */
    shadow &= ~(1U << 8);  /* clear bit 8 */
    shadow ^= (1U << 3);   /* toggle bit 3 */

    printf("shadow=0x%04lX\n", (unsigned long)shadow);
    return 0;
}
