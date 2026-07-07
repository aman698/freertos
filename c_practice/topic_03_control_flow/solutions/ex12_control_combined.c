/*
 * ex12_control_combined.c — Sensor pipeline with mixed control flow
 * Key concept: combine poll, filter, threshold, and action in one loop.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

static uint8_t sample_index;
static const uint16_t raw_stream[] = { 2100, 5000, 2120, 800, 3600, 2110 };

static bool poll_new_sample(uint16_t *out)
{
    if (sample_index >= sizeof(raw_stream) / sizeof(raw_stream[0])) {
        return false;
    }
    *out = raw_stream[sample_index++];
    return true;
}

int main(void)
{
    uint16_t value;
    uint32_t valid_sum = 0U;
    uint32_t valid_n = 0U;
    uint32_t alarm_count = 0U;
    const uint16_t alarm_limit = 3500U;

    printf("=== Sensor pipeline ===\n");

    while (poll_new_sample(&value)) {
        if (value < 1000U || value > 4000U) {
            printf("Sample %u: REJECTED\n", value);
            continue;
        }

        valid_sum += value;
        valid_n++;

        if (value > alarm_limit) {
            alarm_count++;
            printf("Sample %u: ALARM (over %u)\n", value, alarm_limit);
        } else {
            printf("Sample %u: OK\n", value);
        }
    }

    if (valid_n > 0U) {
        printf("Average valid = %lu, alarms = %lu\n",
               (unsigned long)(valid_sum / valid_n), (unsigned long)alarm_count);
    }

    return 0;
}
