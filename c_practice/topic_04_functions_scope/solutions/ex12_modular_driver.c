/*
 * ex12_modular_driver.c — Mini sensor driver with init/read/deinit
 * Key concept: modular functions mirror HAL driver structure.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool initialized;
    uint8_t channel;
    uint16_t last_raw;
} sensor_handle_t;

static int sensor_init(sensor_handle_t *dev, uint8_t channel)
{
    if (dev == NULL) {
        return -1;
    }
    dev->channel = channel;
    dev->last_raw = 0U;
    dev->initialized = true;
    printf("Sensor CH%u init OK\n", channel);
    return 0;
}

static int sensor_read_raw(sensor_handle_t *dev, uint16_t *raw_out)
{
    if (dev == NULL || raw_out == NULL || !dev->initialized) {
        return -1;
    }
    dev->last_raw = 2048U + dev->channel;  /* Simulated ADC */
    *raw_out = dev->last_raw;
    return 0;
}

static void sensor_deinit(sensor_handle_t *dev)
{
    if (dev != NULL) {
        dev->initialized = false;
        printf("Sensor deinit\n");
    }
}

int main(void)
{
    sensor_handle_t dev;
    uint16_t raw = 0U;

    if (sensor_init(&dev, 2) == 0) {
        sensor_read_raw(&dev, &raw);
        printf("Read raw = %u\n", raw);
    }
    sensor_deinit(&dev);

    return 0;
}
