/*
 * ex11_dm1_dtc.c - Build/decode a simplified DM1 active-DTC entry.
 * Key concept: a DTC packs SPN + FMI + occurrence count into a few bytes.
 */
#include <stdint.h>
#include <stdio.h>

/* Simplified illustrative layout (real J1939-73 DM1 framing has more nuance):
 * byte0 = SPN bits 7-0
 * byte1 = SPN bits 15-8
 * byte2 = bits 7-5 SPN bits 18-16, bits 4-0 FMI
 * byte3 = occurrence count (0-127)
 */
typedef struct {
    uint32_t spn;
    uint8_t fmi;
    uint8_t occurrence_count;
} j1939_dtc_t;

static void dm1_encode_dtc(const j1939_dtc_t *dtc, uint8_t out[4])
{
    if ((dtc == NULL) || (out == NULL)) {
        return;
    }

    out[0] = (uint8_t)(dtc->spn & 0xFFU);
    out[1] = (uint8_t)((dtc->spn >> 8) & 0xFFU);
    out[2] = (uint8_t)((((dtc->spn >> 16) & 0x7U) << 5) | (dtc->fmi & 0x1FU));
    out[3] = dtc->occurrence_count & 0x7FU;
}

static void dm1_decode_dtc(const uint8_t in[4], j1939_dtc_t *dtc)
{
    if ((in == NULL) || (dtc == NULL)) {
        return;
    }

    dtc->spn = (uint32_t)in[0] | ((uint32_t)in[1] << 8) | (((uint32_t)in[2] >> 5) << 16);
    dtc->fmi = in[2] & 0x1FU;
    dtc->occurrence_count = in[3] & 0x7FU;
}

int main(void)
{
    /* SPN 110 = Engine Coolant Temp, FMI 0 = data valid but above normal range */
    j1939_dtc_t dtc = {110UL, 0U, 3U};
    uint8_t frame[4];
    j1939_dtc_t decoded;

    dm1_encode_dtc(&dtc, frame);
    printf("DM1 frame: %02X %02X %02X %02X\n", frame[0], frame[1], frame[2], frame[3]);

    dm1_decode_dtc(frame, &decoded);
    printf("Decoded: SPN=%lu, FMI=%u, occurrence_count=%u\n",
           (unsigned long)decoded.spn, decoded.fmi, decoded.occurrence_count);

    return 0;
}
