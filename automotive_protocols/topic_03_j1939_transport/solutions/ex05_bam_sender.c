/*
 * ex05_bam_sender.c - Build a BAM TP.CM + TP.DT sequence for a payload > 8 bytes.
 * Key concept: BAM has no flow control - the whole sequence is sent unsolicited.
 */
#include <stdint.h>
#include <stdio.h>

#define TP_DATA_BYTES_PER_PACKET 7U
#define BAM_CONTROL_BYTE         0x20U

static uint8_t bam_num_packets(uint16_t payload_size)
{
    return (uint8_t)((payload_size + (TP_DATA_BYTES_PER_PACKET - 1U)) / TP_DATA_BYTES_PER_PACKET);
}

static void bam_build_tp_cm(uint16_t payload_size, uint32_t pgn, uint8_t out[8])
{
    if (out == NULL) {
        return;
    }

    out[0] = BAM_CONTROL_BYTE;
    out[1] = (uint8_t)(payload_size & 0xFFU);
    out[2] = (uint8_t)((payload_size >> 8) & 0xFFU);
    out[3] = bam_num_packets(payload_size);
    out[4] = 0xFFU; /* Reserved */
    out[5] = (uint8_t)(pgn & 0xFFU);
    out[6] = (uint8_t)((pgn >> 8) & 0xFFU);
    out[7] = (uint8_t)((pgn >> 16) & 0xFFU);
}

static void bam_build_tp_dt(const uint8_t *payload, uint16_t payload_size, uint8_t seq, uint8_t out[8])
{
    uint8_t i;
    uint16_t base;

    if ((payload == NULL) || (out == NULL) || (seq == 0U)) {
        return;
    }

    out[0] = seq;
    base = (uint16_t)((seq - 1U) * TP_DATA_BYTES_PER_PACKET);

    for (i = 0U; i < TP_DATA_BYTES_PER_PACKET; i++) {
        uint16_t idx = (uint16_t)(base + i);
        out[i + 1U] = (idx < payload_size) ? payload[idx] : 0xFFU;
    }
}

static void print_frame(const char *label, const uint8_t frame[8])
{
    uint8_t i;

    printf("%s:", label);
    for (i = 0U; i < 8U; i++) {
        printf(" %02X", frame[i]);
    }
    printf("\n");
}

int main(void)
{
    uint8_t payload[] = {0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U, 0x88U, 0x99U, 0xAAU};
    uint16_t payload_size = (uint16_t)sizeof(payload);
    uint32_t target_pgn = 65226UL; /* DM1 as a stand-in multi-packet message */
    uint8_t num_packets = bam_num_packets(payload_size);
    uint8_t frame[8];
    uint8_t seq;

    printf("Payload size = %u bytes, num packets = %u\n", payload_size, num_packets);

    bam_build_tp_cm(payload_size, target_pgn, frame);
    print_frame("TP.CM (BAM)", frame);

    for (seq = 1U; seq <= num_packets; seq++) {
        bam_build_tp_dt(payload, payload_size, seq, frame);
        print_frame("TP.DT", frame);
    }

    return 0;
}
