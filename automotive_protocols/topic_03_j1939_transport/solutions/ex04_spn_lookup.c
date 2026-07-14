/*
 * ex04_spn_lookup.c - Look up an SPN and decode a raw byte with its scaling.
 * Key concept: an SPN lives inside a PGN's payload and needs resolution/offset to scale.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t spn;
    const char *name;
    const char *unit;
    float resolution;
    float offset;
} spn_entry_t;

/* Illustrative subset only - real J1939-71 tables have thousands of entries. */
static const spn_entry_t spn_table[] = {
    {190U, "Engine Speed",            "rpm",  0.125f,   0.0f},
    {110U, "Engine Coolant Temp",     "degC", 1.0f,   -40.0f},
    {84U,  "Wheel-Based Vehicle Speed", "km/h", 0.00390625f, 0.0f},
};

static const spn_entry_t *spn_lookup(uint16_t spn)
{
    size_t count = sizeof(spn_table) / sizeof(spn_table[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        if (spn_table[i].spn == spn) {
            return &spn_table[i];
        }
    }

    return NULL;
}

static void spn_decode_and_print(uint16_t spn, uint16_t raw)
{
    const spn_entry_t *entry = spn_lookup(spn);
    float physical;

    if (entry == NULL) {
        printf("SPN %u: not found in table\n", spn);
        return;
    }

    physical = ((float)raw * entry->resolution) + entry->offset;
    printf("SPN %u (%s): raw=%u -> %.3f %s\n", spn, entry->name, raw, (double)physical, entry->unit);
}

int main(void)
{
    spn_decode_and_print(190U, 1600U);   /* Engine speed raw counts */
    spn_decode_and_print(110U, 105U);    /* Coolant temp raw byte */
    spn_decode_and_print(999U, 42U);     /* Not in table */

    return 0;
}
