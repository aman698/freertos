/*
 * ex10_protocol_picker.c — Recommend a serial protocol for a stated ECU communication need
 * Key concept: distance, node count, and throughput requirements point to different automotive buses.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef enum {
    NEED_LONG_DISTANCE = 0,
    NEED_MULTI_DROP,
    NEED_HIGH_THROUGHPUT,
    NEED_CHIP_TO_CHIP_SIMPLE
} comm_need_t;

typedef struct {
    comm_need_t need;
    const char *label;
} need_entry_t;

static const char *pick_protocol(comm_need_t need, const char **reason)
{
    const char *protocol;

    if (reason == NULL) {
        return "N/A";
    }

    switch (need) {
    case NEED_LONG_DISTANCE:
        protocol = "CAN";
        *reason = "differential signaling rejects noise over long harness runs";
        break;
    case NEED_MULTI_DROP:
        protocol = "CAN";
        *reason = "built-in arbitration lets many ECUs share one bus without a master";
        break;
    case NEED_HIGH_THROUGHPUT:
        protocol = "SPI";
        *reason = "full-duplex shift register moves bytes fastest between two chips";
        break;
    case NEED_CHIP_TO_CHIP_SIMPLE:
    default:
        protocol = "I2C";
        *reason = "two shared wires are enough for low-speed sensor/EEPROM access";
        break;
    }
    return protocol;
}

int main(void)
{
    const need_entry_t needs[] = {
        { NEED_LONG_DISTANCE, "Long wiring harness across the vehicle" },
        { NEED_MULTI_DROP, "Many ECUs on one shared bus" },
        { NEED_HIGH_THROUGHPUT, "Fast MCU-to-CAN-controller data path" },
        { NEED_CHIP_TO_CHIP_SIMPLE, "Read a board-level EEPROM or sensor" },
    };
    size_t i;

    for (i = 0U; i < sizeof(needs) / sizeof(needs[0]); i++) {
        const char *reason = NULL;
        const char *protocol = pick_protocol(needs[i].need, &reason);

        printf("Need: %-38s -> %-4s (%s)\n", needs[i].label, protocol, reason);
    }
    return 0;
}
