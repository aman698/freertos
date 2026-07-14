/* ex01_single_frame.c - Build and parse an ISO-TP Single Frame (N_PCI type 0x0). */
/* Key concept: SF low nibble of byte 0 holds SF_DL (0-7) for classic 8-byte CAN. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC        8U
#define SF_MAX_LEN     7U
#define SF_PCI_TYPE    0x00U

static int32_t build_single_frame(uint8_t *frame, const uint8_t *payload, uint8_t len)
{
    if ((frame == NULL) || (payload == NULL) || (len > SF_MAX_LEN)) {
        return -1;
    }

    memset(frame, 0, CAN_DLC);
    frame[0] = (uint8_t)(SF_PCI_TYPE | len);
    for (uint8_t i = 0U; i < len; i++) {
        frame[1U + i] = payload[i];
    }
    return 0;
}

static int32_t parse_single_frame(const uint8_t *frame, uint8_t *payload, uint8_t *len_out)
{
    uint8_t pci_type;
    uint8_t sf_dl;

    if ((frame == NULL) || (payload == NULL) || (len_out == NULL)) {
        return -1;
    }

    pci_type = (uint8_t)(frame[0] >> 4);
    sf_dl = (uint8_t)(frame[0] & 0x0FU);
    if ((pci_type != 0x0U) || (sf_dl > SF_MAX_LEN)) {
        return -1;
    }

    for (uint8_t i = 0U; i < sf_dl; i++) {
        payload[i] = frame[1U + i];
    }
    *len_out = sf_dl;
    return 0;
}

int main(void)
{
    const uint8_t original[4] = {0x11U, 0x22U, 0x33U, 0x44U};
    uint8_t frame[CAN_DLC];
    uint8_t recovered[SF_MAX_LEN];
    uint8_t recovered_len = 0U;

    if (build_single_frame(frame, original, (uint8_t)sizeof(original)) != 0) {
        printf("build failed\n");
        return 0;
    }

    printf("SF frame:");
    for (uint8_t i = 0U; i < CAN_DLC; i++) {
        printf(" 0x%02X", frame[i]);
    }
    printf("\n");

    if (parse_single_frame(frame, recovered, &recovered_len) != 0) {
        printf("parse failed\n");
        return 0;
    }

    printf("Parsed length: %u\n", recovered_len);
    printf("Payload match: %s\n",
           (memcmp(original, recovered, recovered_len) == 0) ? "yes" : "no");

    return 0;
}
