/*
 * ex01_id_pack_unpack.c - Pack/unpack a 29-bit J1939 CAN ID.
 * Key concept: priority, PGN, and source address share one 29-bit field.
 */
#include <stdint.h>
#include <stdio.h>

#define J1939_PRIO_MASK   0x7U
#define J1939_PGN_MASK    0x3FFFFU
#define J1939_SA_MASK     0xFFU

static uint32_t j1939_pack_id(uint8_t priority, uint32_t pgn, uint8_t sa)
{
    uint32_t id = 0U;

    id |= ((uint32_t)(priority & J1939_PRIO_MASK)) << 26;
    id |= ((uint32_t)(pgn & J1939_PGN_MASK)) << 8;
    id |= (uint32_t)sa;

    return id;
}

static void j1939_unpack_id(uint32_t id, uint8_t *priority, uint32_t *pgn, uint8_t *sa)
{
    if ((priority == NULL) || (pgn == NULL) || (sa == NULL)) {
        return;
    }

    *priority = (uint8_t)((id >> 26) & J1939_PRIO_MASK);
    *pgn = (id >> 8) & J1939_PGN_MASK;
    *sa = (uint8_t)(id & J1939_SA_MASK);
}

int main(void)
{
    uint8_t priority_in = 3U;
    uint32_t pgn_in = 61444UL;   /* EEC1 */
    uint8_t sa_in = 0x00U;      /* Engine controller */

    uint32_t id = j1939_pack_id(priority_in, pgn_in, sa_in);

    uint8_t priority_out = 0U;
    uint32_t pgn_out = 0U;
    uint8_t sa_out = 0U;

    j1939_unpack_id(id, &priority_out, &pgn_out, &sa_out);

    printf("Packed ID   = 0x%08X\n", id);
    printf("Priority    = %u (in), %u (out)\n", priority_in, priority_out);
    printf("PGN         = %lu (in), %lu (out)\n", (unsigned long)pgn_in, (unsigned long)pgn_out);
    printf("Source addr = 0x%02X (in), 0x%02X (out)\n", sa_in, sa_out);

    if ((priority_in == priority_out) && (pgn_in == pgn_out) && (sa_in == sa_out)) {
        printf("Round trip OK\n");
    } else {
        printf("Round trip MISMATCH\n");
    }

    return 0;
}
