/*
 * ex06_bam_receiver.c - Reassemble TP.DT packets into the original payload.
 * Key concept: TP.CM supplies total size and packet count needed to stop reassembly.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define TP_DATA_BYTES_PER_PACKET 7U
#define MAX_PAYLOAD_BYTES        64U

typedef struct {
    uint16_t total_size;
    uint8_t total_packets;
    uint32_t pgn;
} bam_session_t;

static bool bam_parse_tp_cm(const uint8_t frame[8], bam_session_t *session)
{
    if ((frame == NULL) || (session == NULL)) {
        return false;
    }

    session->total_size = (uint16_t)(frame[1] | ((uint16_t)frame[2] << 8));
    session->total_packets = frame[3];
    session->pgn = (uint32_t)frame[5] | ((uint32_t)frame[6] << 8) | ((uint32_t)frame[7] << 16);

    return true;
}

static bool bam_accumulate_tp_dt(const uint8_t frame[8], uint8_t *reassembly, uint16_t total_size)
{
    uint8_t seq;
    uint8_t i;
    uint16_t base;

    if ((frame == NULL) || (reassembly == NULL)) {
        return false;
    }

    seq = frame[0];
    if (seq == 0U) {
        return false;
    }

    base = (uint16_t)((seq - 1U) * TP_DATA_BYTES_PER_PACKET);

    for (i = 0U; i < TP_DATA_BYTES_PER_PACKET; i++) {
        uint16_t idx = (uint16_t)(base + i);
        if (idx < total_size) {
            reassembly[idx] = frame[i + 1U];
        }
    }

    return true;
}

int main(void)
{
    /* Same session ex05 produced: 10-byte payload, PGN 65226 (DM1). */
    const uint8_t tp_cm[8] = {0x20U, 0x0AU, 0x00U, 0x02U, 0xFFU, 0xCAU, 0xFEU, 0x00U};
    const uint8_t tp_dt1[8] = {0x01U, 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U};
    const uint8_t tp_dt2[8] = {0x02U, 0x88U, 0x99U, 0xAAU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

    bam_session_t session = {0U, 0U, 0UL};
    uint8_t reassembly[MAX_PAYLOAD_BYTES] = {0U};
    uint16_t i;

    bam_parse_tp_cm(tp_cm, &session);
    printf("Session: size=%u bytes, packets=%u, PGN=%lu\n",
           session.total_size, session.total_packets, (unsigned long)session.pgn);

    bam_accumulate_tp_dt(tp_dt1, reassembly, session.total_size);
    bam_accumulate_tp_dt(tp_dt2, reassembly, session.total_size);

    printf("Reassembled:");
    for (i = 0U; i < session.total_size; i++) {
        printf(" %02X", reassembly[i]);
    }
    printf("\n");

    return 0;
}
