/*
 * ex04_flexray_static_slot.c - FlexRay static segment slot-timing calculator.
 * Key concept: fixed-duration slots make the active slot ID a simple function of time.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint16_t flexray_slot_at_offset(uint32_t offset_us, uint16_t slot_duration_us,
                                       uint16_t num_static_slots)
{
    if ((slot_duration_us == 0U) || (num_static_slots == 0U)) {
        return 0U;
    }
    uint32_t slot_index = offset_us / slot_duration_us;
    return (uint16_t)(slot_index % num_static_slots);
}

int main(void)
{
    const uint16_t slot_duration_us = 25U;
    const uint16_t num_static_slots = 20U;
    const uint32_t cycle_length_us = (uint32_t)slot_duration_us * num_static_slots;
    uint32_t offsets_us[] = {0U, 25U, 130U, 490U, 500U, 525U};
    size_t count = sizeof(offsets_us) / sizeof(offsets_us[0]);

    printf("Static segment: %u slots x %u us = %lu us per cycle\n",
           num_static_slots, slot_duration_us, (unsigned long)cycle_length_us);

    for (size_t i = 0U; i < count; i++) {
        uint16_t slot = flexray_slot_at_offset(offsets_us[i], slot_duration_us, num_static_slots);
        uint32_t cycle = offsets_us[i] / cycle_length_us;

        printf("Offset %4lu us -> cycle %lu, slot ID %2u\n",
               (unsigned long)offsets_us[i], (unsigned long)cycle, slot);
    }

    return 0;
}
