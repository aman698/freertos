/*
 * ex03_pgn_extraction.c - Extract the PGN from a raw 29-bit CAN ID.
 * Key concept: PDU1 zeroes PS out of the PGN; PDU2 folds PS into the PGN.
 */
#include <stdint.h>
#include <stdio.h>

#define J1939_PDU2_THRESHOLD 240U

static uint32_t j1939_extract_pgn(uint32_t can_id)
{
    uint8_t r_dp = (uint8_t)((can_id >> 24) & 0x3U); /* Reserved + Data Page */
    uint8_t pf = (uint8_t)((can_id >> 16) & 0xFFU);
    uint8_t ps = (uint8_t)((can_id >> 8) & 0xFFU);
    uint32_t pgn;

    if (pf >= J1939_PDU2_THRESHOLD) {
        pgn = ((uint32_t)r_dp << 16) | ((uint32_t)pf << 8) | (uint32_t)ps;
    } else {
        pgn = ((uint32_t)r_dp << 16) | ((uint32_t)pf << 8);
    }

    return pgn;
}

int main(void)
{
    /* PDU1 example: priority 6, PF=0xEA (request, PDU1), PS=0xFF (global), SA=0x00 */
    uint32_t id_pdu1 = 0x18EAFF00UL;
    /* PDU2 example: priority 3, PGN 61444 (0xF004, EEC1), SA=0x00 */
    uint32_t id_pdu2 = 0x0CF00400UL;

    uint32_t pgn1 = j1939_extract_pgn(id_pdu1);
    uint32_t pgn2 = j1939_extract_pgn(id_pdu2);

    printf("ID 0x%08X -> PGN %lu (0x%04lX) [PDU1]\n",
           id_pdu1, (unsigned long)pgn1, (unsigned long)pgn1);
    printf("ID 0x%08X -> PGN %lu (0x%04lX) [PDU2]\n",
           id_pdu2, (unsigned long)pgn2, (unsigned long)pgn2);

    return 0;
}
