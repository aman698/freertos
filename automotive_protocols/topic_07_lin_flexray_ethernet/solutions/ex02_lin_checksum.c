/*
 * ex02_lin_checksum.c - LIN classic vs enhanced checksum over a data buffer.
 * Key concept: enhanced checksum folds the PID into the sum; classic sums data only.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint8_t lin_checksum(const uint8_t *data, size_t len, uint8_t pid, int include_pid)
{
    uint16_t sum = 0U;

    if (data == NULL) {
        return 0U;
    }
    if (include_pid != 0) {
        sum = (uint16_t)(sum + pid);
        if (sum > 0xFFU) {
            sum = (uint16_t)(sum - 0xFFU);
        }
    }
    for (size_t i = 0U; i < len; i++) {
        sum = (uint16_t)(sum + data[i]);
        if (sum > 0xFFU) {
            sum = (uint16_t)(sum - 0xFFU);
        }
    }
    return (uint8_t)(~sum & 0xFFU);
}

int main(void)
{
    uint8_t data[] = {0x4AU, 0x00U, 0x01U, 0xFFU};
    size_t len = sizeof(data) / sizeof(data[0]);
    uint8_t pid = 0x8FU;

    uint8_t classic = lin_checksum(data, len, pid, 0);
    uint8_t enhanced = lin_checksum(data, len, pid, 1);

    printf("PID 0x%02X, data bytes: ", pid);
    for (size_t i = 0U; i < len; i++) {
        printf("0x%02X ", data[i]);
    }
    printf("\n");

    printf("Classic checksum  (data only)   = 0x%02X\n", classic);
    printf("Enhanced checksum (PID + data)  = 0x%02X\n", enhanced);
    printf("Difference: enhanced folds the PID byte into the running sum before inverting.\n");

    return 0;
}
