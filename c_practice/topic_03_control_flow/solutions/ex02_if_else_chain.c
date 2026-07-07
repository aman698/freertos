/*
 * ex02_if_else_chain.c — Temperature zone classification
 * Key concept: if-else chain maps continuous value to discrete zones.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int16_t temp_c = 42;  /* Signed sensor reading in Celsius */

    printf("Temperature = %d C -> ", temp_c);

    if (temp_c < 0) {
        printf("LOW (freeze risk)\n");
    } else if (temp_c <= 35) {
        printf("OK (normal range)\n");
    } else {
        printf("HIGH (cooling needed)\n");
    }

    temp_c = -5;
    printf("Temperature = %d C -> ", temp_c);
    if (temp_c < 0) {
        printf("LOW (freeze risk)\n");
    } else if (temp_c <= 35) {
        printf("OK (normal range)\n");
    } else {
        printf("HIGH (cooling needed)\n");
    }

    return 0;
}
