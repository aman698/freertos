/*
 * ex12_priority_arbitration.c - Show how J1939 priority changes CAN arbitration.
 * Key concept: a lower 29-bit ID is dominant and wins bitwise CAN arbitration.
 */
#include <stdint.h>
#include <stdio.h>

static uint32_t j1939_pack_id(uint8_t priority, uint32_t pgn, uint8_t sa)
{
    uint32_t id = 0U;

    id |= ((uint32_t)(priority & 0x7U)) << 26;
    id |= ((uint32_t)(pgn & 0x3FFFFU)) << 8;
    id |= (uint32_t)sa;

    return id;
}

int main(void)
{
    uint32_t pgn = 61444UL; /* EEC1, same message on both nodes */

    /* Same PGN and source, only priority differs. */
    uint32_t id_high_prio = j1939_pack_id(3U, pgn, 0x00U);  /* typical EEC1 priority */
    uint32_t id_low_prio = j1939_pack_id(6U, pgn, 0x00U);   /* artificially lowered priority */

    printf("Priority 3 -> ID 0x%08X\n", id_high_prio);
    printf("Priority 6 -> ID 0x%08X\n", id_low_prio);

    if (id_high_prio < id_low_prio) {
        printf("Priority 3 frame wins arbitration (lower ID is dominant on the bus)\n");
    } else {
        printf("Priority 6 frame wins arbitration (lower ID is dominant on the bus)\n");
    }

    return 0;
}
