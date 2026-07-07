/*
 * ex10_relational.c — Compare ADC value to thresholds
 */
#include <stdint.h>
#include <stdio.h>

typedef enum { ZONE_LOW, ZONE_OK, ZONE_HIGH } Zone_t;

static Zone_t classify_adc(uint16_t raw)
{
    if (raw < 500U) {
        return ZONE_LOW;
    }
    if (raw > 3500U) {
        return ZONE_HIGH;
    }
    return ZONE_OK;
}

int main(void)
{
    const char *names[] = { "LOW", "OK", "HIGH" };
    uint16_t samples[] = { 100U, 2048U, 4000U };

    for (unsigned i = 0U; i < 3U; i++) {
        printf("ADC %u -> %s\n", samples[i], names[classify_adc(samples[i])]);
    }
    return 0;
}
