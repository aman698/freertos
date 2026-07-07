/*
 * ex11_goto_cleanup.c — Driver init with goto error cleanup
 * Key concept: goto single exit label is idiomatic for init/teardown in drivers.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

static bool clock_enable(void)  { return true; }
static bool gpio_config(void)   { return true; }
static bool dma_config(void)    { return false; }  /* Simulated failure */

static int sensor_driver_init(void)
{
    int result = 0;

    if (!clock_enable()) {
        result = -1;
        goto cleanup;
    }
    printf("Clock: OK\n");

    if (!gpio_config()) {
        result = -2;
        goto cleanup;
    }
    printf("GPIO: OK\n");

    if (!dma_config()) {
        result = -3;
        goto cleanup;
    }
    printf("DMA: OK\n");

    printf("Sensor driver init SUCCESS\n");
    return 0;

cleanup:
    printf("Cleanup: disable clocks, release pins (err=%d)\n", result);
    return result;
}

int main(void)
{
    int rc = sensor_driver_init();
    printf("Return code = %d\n", rc);
    return 0;
}
