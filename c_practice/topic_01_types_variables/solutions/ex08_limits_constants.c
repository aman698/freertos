/*
 * ex08_limits_constants.c — Min/max macros from stdint.h
 * Key concept: use limit macros instead of magic numbers.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    printf("=== stdint.h limit constants ===\n");
    printf("UINT8_MAX  = %u\n",  UINT8_MAX);
    printf("INT8_MIN   = %d\n",  INT8_MIN);
    printf("INT8_MAX   = %d\n",  INT8_MAX);
    printf("UINT16_MAX = %u\n", UINT16_MAX);
    printf("INT16_MIN  = %d\n", INT16_MIN);
    printf("INT16_MAX  = %d\n", INT16_MAX);
    printf("UINT32_MAX = %lu\n", (unsigned long)UINT32_MAX);

    /* Embedded: clamp ADC to 12-bit range using mask, not INT16_MAX */
    uint16_t adc = 5000;
    adc &= 0x0FFF; /* 12-bit mask */
    printf("\n12-bit ADC clamped: %u (max 4095)\n", adc);

    return 0;
}
