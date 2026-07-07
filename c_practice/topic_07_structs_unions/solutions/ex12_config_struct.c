/*
 * ex12_config_struct.c — Device config struct with defaults
 * Key concept: config structs centralize tunable parameters.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    uint32_t sample_rate_hz;
    uint8_t  gain;
    bool     filter_enable;
    uint16_t alarm_threshold;
} adc_config_t;

static const adc_config_t ADC_DEFAULT_CONFIG = {
    .sample_rate_hz = 1000UL,
    .gain = 1U,
    .filter_enable = true,
    .alarm_threshold = 3500U
};

static void print_config(const adc_config_t *cfg)
{
    printf("ADC config: rate=%lu Hz gain=%u filter=%s threshold=%u\n",
           (unsigned long)cfg->sample_rate_hz,
           cfg->gain,
           cfg->filter_enable ? "ON" : "OFF",
           cfg->alarm_threshold);
}

int main(void)
{
    adc_config_t cfg = ADC_DEFAULT_CONFIG;
    cfg.gain = 4U;
    print_config(&cfg);
    return 0;
}
