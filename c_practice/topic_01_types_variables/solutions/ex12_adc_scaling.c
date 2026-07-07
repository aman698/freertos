/*
 * ex12_adc_scaling.c — Scale 12-bit uint16_t ADC to millivolts
 * Key concept: use uint16_t for raw ADC; uint32_t for intermediate math.
 */
#include <stdint.h>
#include <stdio.h>

#define ADC_MAX_COUNTS  4095U   /* 12-bit ADC */
#define VREF_MV         3300U   /* 3.3 V reference */

int main(void)
{
    uint16_t adc_raw = 4095; /* full-scale reading */

    /* Promote to uint32_t to avoid overflow in multiply */
    uint32_t mv = ((uint32_t)adc_raw * VREF_MV) / ADC_MAX_COUNTS;

    printf("ADC raw:  %u counts (12-bit max %u)\n", adc_raw, ADC_MAX_COUNTS);
    printf("Voltage:  %lu mV\n", (unsigned long)mv);

    adc_raw = 2048; /* ~half scale */
    mv = ((uint32_t)adc_raw * VREF_MV) / ADC_MAX_COUNTS;
    printf("Half-scale: %lu mV\n", (unsigned long)mv);

    return 0;
}
