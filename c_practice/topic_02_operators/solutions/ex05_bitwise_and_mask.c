/*
 * ex05_bitwise_and_mask.c — Read GPIO pin state with AND mask
 */
#include <stdint.h>
#include <stdio.h>

#define PIN5_MASK  (1U << 5)

int main(void)
{
    uint16_t idr = 0x0020U;  /* pin 5 high */

    if (idr & PIN5_MASK) {
        printf("Pin 5 is HIGH\n");
    } else {
        printf("Pin 5 is LOW\n");
    }
    return 0;
}
