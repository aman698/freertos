/*
 * ex10_sizeof_pitfall.c — sizeof type vs sizeof pointer
 * Key concept: pointers are 4 bytes (32-bit MCU) or 8 bytes (64-bit PC).
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t  counter = 0;
    uint32_t *p_counter = &counter;

    printf("sizeof(uint32_t)   = %zu byte(s)\n", sizeof(uint32_t));
    printf("sizeof(uint32_t*)  = %zu byte(s)\n", sizeof(uint32_t *));
    printf("sizeof(counter)    = %zu\n", sizeof(counter));
    printf("sizeof(p_counter)  = %zu\n", sizeof(p_counter));

    /* Common mistake: expecting sizeof(array) when parameter decayed to pointer */
    uint8_t sensor_buf[16];
    printf("\nsensor_buf array  = %zu bytes\n", sizeof(sensor_buf));
    printf("pointer to buf    = %zu bytes (address size, not 16)\n",
           sizeof(uint8_t *));

    return 0;
}
