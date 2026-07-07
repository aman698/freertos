/*
 * ex06_nested_struct.c — Nested struct for composite device state
 * Key concept: struct members can be other structs.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} vec3_t;

typedef struct {
    vec3_t   accel;
    uint32_t timestamp_ms;
} imu_sample_t;

int main(void)
{
    imu_sample_t sample = {
        .accel = { .x = 100, .y = -50, .z = 980 },
        .timestamp_ms = 12345UL
    };

    printf("IMU @ %lu ms: x=%u y=%d z=%u\n",
           (unsigned long)sample.timestamp_ms,
           sample.accel.x,
           (int)sample.accel.y,
           sample.accel.z);
    return 0;
}
