/* ex03_consecutive_frame.c - Build and parse ISO-TP Consecutive Frames (N_PCI type 0x2). */
/* Key concept: SN is a 4-bit rolling counter (0-15) starting at 1 after the First Frame. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC          8U
#define CF_PCI_TYPE      0x20U
#define CF_DATA_BYTES    7U
#define SN_MASK          0x0FU

static int32_t build_consecutive_frame(uint8_t *frame, const uint8_t *payload, uint8_t len, uint8_t sn)
{
    if ((frame == NULL) || (payload == NULL) || (len > CF_DATA_BYTES)) {
        return -1;
    }

    memset(frame, 0, CAN_DLC);
    frame[0] = (uint8_t)(CF_PCI_TYPE | (sn & SN_MASK));
    for (uint8_t i = 0U; i < len; i++) {
        frame[1U + i] = payload[i];
    }
    return 0;
}

static int32_t parse_consecutive_frame(const uint8_t *frame, uint8_t *payload, uint8_t *sn_out)
{
    uint8_t pci_type;

    if ((frame == NULL) || (payload == NULL) || (sn_out == NULL)) {
        return -1;
    }

    pci_type = (uint8_t)(frame[0] >> 4);
    if (pci_type != 0x2U) {
        return -1;
    }

    *sn_out = (uint8_t)(frame[0] & SN_MASK);
    for (uint8_t i = 0U; i < CF_DATA_BYTES; i++) {
        payload[i] = frame[1U + i];
    }
    return 0;
}

int main(void)
{
    uint8_t payload[CF_DATA_BYTES];
    uint8_t frame[CAN_DLC];
    uint8_t parsed_payload[CF_DATA_BYTES];
    uint8_t parsed_sn = 0U;

    for (uint8_t i = 0U; i < CF_DATA_BYTES; i++) {
        payload[i] = (uint8_t)(0xA0U + i);
    }

    /* Demonstrate SN rolling over past 15 back to 0. */
    for (uint16_t sn = 14U; sn <= 17U; sn++) {
        if (build_consecutive_frame(frame, payload, CF_DATA_BYTES, (uint8_t)sn) != 0) {
            printf("build failed\n");
            return 0;
        }

        if (parse_consecutive_frame(frame, parsed_payload, &parsed_sn) != 0) {
            printf("parse failed\n");
            return 0;
        }

        printf("Requested SN=%2u -> frame byte0=0x%02X -> parsed SN=%u\n",
               sn, frame[0], parsed_sn);
    }

    return 0;
}
