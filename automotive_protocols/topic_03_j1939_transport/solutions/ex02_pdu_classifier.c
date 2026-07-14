/*
 * ex02_pdu_classifier.c - Classify PDU Format bytes as PDU1 or PDU2.
 * Key concept: PF < 240 is peer-to-peer (PDU1); PF >= 240 is broadcast (PDU2).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define J1939_PDU2_THRESHOLD 240U

static bool j1939_is_pdu2(uint8_t pf)
{
    return pf >= J1939_PDU2_THRESHOLD;
}

static void j1939_classify(uint8_t pf)
{
    if (j1939_is_pdu2(pf)) {
        printf("PF = 0x%02X -> PDU2 (broadcast), PS = group extension\n", pf);
    } else {
        printf("PF = 0x%02X -> PDU1 (peer-to-peer), PS = destination address\n", pf);
    }
}

int main(void)
{
    uint8_t samples[] = {0x00U, 0xEAU, 0xEFU, 0xF0U, 0xFEU, 0xFFU};
    size_t count = sizeof(samples) / sizeof(samples[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        j1939_classify(samples[i]);
    }

    return 0;
}
