/*
 * ex03_lin_schedule_table.c - Simulate a LIN master schedule table.
 * Key concept: the master drives every frame; slaves only respond when addressed.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t frame_id;
    uint8_t period_ticks;
    const char *name;
} ScheduleEntry_t;

static const ScheduleEntry_t schedule_table[] = {
    {0x01U, 1U, "WindowSwitch"},
    {0x10U, 2U, "MirrorPos"},
    {0x20U, 4U, "SeatHeater"},
};

static void run_schedule(const ScheduleEntry_t *table, size_t entries, uint8_t ticks)
{
    if (table == NULL) {
        return;
    }
    for (uint8_t tick = 0U; tick < ticks; tick++) {
        printf("Tick %2u: ", tick);
        for (size_t i = 0U; i < entries; i++) {
            if ((tick % table[i].period_ticks) == 0U) {
                printf("[ID 0x%02X %s] ", table[i].frame_id, table[i].name);
            }
        }
        printf("\n");
    }
}

int main(void)
{
    size_t entries = sizeof(schedule_table) / sizeof(schedule_table[0]);

    printf("LIN schedule table simulation (period in ticks):\n");
    run_schedule(schedule_table, entries, 8U);

    return 0;
}
