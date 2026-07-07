/*
 * ex05_static_file_scope.c — File-static hides implementation details
 * Key concept: static at file scope limits symbol visibility to this file.
 */
#include <stdint.h>
#include <stdio.h>

static uint16_t adc_raw_to_mv(uint16_t raw)
{
    return (uint16_t)((raw * 3300U) / 4095U);
}

static uint16_t read_adc_channel(uint8_t channel)
{
    (void)channel;
    return 2048U;  /* Simulated mid-scale reading */
}

uint16_t sensor_read_mv(uint8_t channel)
{
    return adc_raw_to_mv(read_adc_channel(channel));
}

int main(void)
{
    printf("Sensor CH0 = %u mV\n", sensor_read_mv(0));
    printf("(adc_raw_to_mv is file-static — not exported)\n");
    return 0;
}
