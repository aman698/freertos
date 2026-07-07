/*
 * ex11_stdbool_flags.c — bool flags for device status
 * Key concept: stdbool.h gives readable true/false for status bits.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    bool sensor_ready = false;
    bool alarm_active = false;
    bool tx_busy      = true;

    /* Simulate sensor init complete */
    sensor_ready = true;

    /* Over-temperature trip */
    int16_t temp_c = 85;
    if (temp_c > 80) {
        alarm_active = true;
    }

    printf("sensor_ready = %s\n", sensor_ready ? "true" : "false");
    printf("alarm_active = %s\n", alarm_active ? "true" : "false");
    printf("tx_busy      = %s\n", tx_busy ? "true" : "false");
    printf("sizeof(bool) = %zu (often 1 byte)\n", sizeof(bool));

    return 0;
}
