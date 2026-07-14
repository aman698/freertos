/* ex02_first_frame.c - Build and parse an ISO-TP First Frame (N_PCI type 0x1). */
/* Key concept: 12-bit FF_DL spans byte0's low nibble and all of byte1. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC          8U
#define FF_PCI_TYPE      0x10U
#define FF_DATA_BYTES    6U
#define FF_DL_MAX        4095U

static int32_t build_first_frame(uint8_t *frame, const uint8_t *payload, uint16_t total_len)
{
    if ((frame == NULL) || (payload == NULL) || (total_len > FF_DL_MAX)) {
        return -1;
    }

    memset(frame, 0, CAN_DLC);
    frame[0] = (uint8_t)(FF_PCI_TYPE | ((total_len >> 8) & 0x0FU));
    frame[1] = (uint8_t)(total_len & 0xFFU);
    for (uint8_t i = 0U; i < FF_DATA_BYTES; i++) {
        frame[2U + i] = payload[i];
    }
    return 0;
}

static int32_t parse_first_frame(const uint8_t *frame, uint16_t *total_len_out, uint8_t *first_data)
{
    uint8_t pci_type;

    if ((frame == NULL) || (total_len_out == NULL) || (first_data == NULL)) {
        return -1;
    }

    pci_type = (uint8_t)(frame[0] >> 4);
    if (pci_type != 0x1U) {
        return -1;
    }

    *total_len_out = (uint16_t)(((uint16_t)(frame[0] & 0x0FU) << 8) | frame[1]);
    for (uint8_t i = 0U; i < FF_DATA_BYTES; i++) {
        first_data[i] = frame[2U + i];
    }
    return 0;
}

int main(void)
{
    uint8_t payload[20];
    uint8_t frame[CAN_DLC];
    uint16_t parsed_len = 0U;
    uint8_t first_data[FF_DATA_BYTES];

    for (uint8_t i = 0U; i < (uint8_t)sizeof(payload); i++) {
        payload[i] = i;
    }

    if (build_first_frame(frame, payload, (uint16_t)sizeof(payload)) != 0) {
        printf("build failed\n");
        return 0;
    }

    printf("FF frame:");
    for (uint8_t i = 0U; i < CAN_DLC; i++) {
        printf(" 0x%02X", frame[i]);
    }
    printf("\n");

    if (parse_first_frame(frame, &parsed_len, first_data) != 0) {
        printf("parse failed\n");
        return 0;
    }

    printf("FF_DL (total length) = %u\n", parsed_len);
    printf("First 6 payload bytes:");
    for (uint8_t i = 0U; i < FF_DATA_BYTES; i++) {
        printf(" 0x%02X", first_data[i]);
    }
    printf("\n");

    return 0;
}
