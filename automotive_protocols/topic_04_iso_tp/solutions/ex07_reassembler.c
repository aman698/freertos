/* ex07_reassembler.c - Reassemble an ISO-TP FF + CF frame stream back into a payload. */
/* Key concept: consecutive-frame SN must increment by one (mod 16, skipping 0) with no gaps. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC          8U
#define FF_DATA_BYTES    6U
#define CF_DATA_BYTES    7U
#define MAX_PAYLOAD     64U

static int32_t reassemble_message(const uint8_t frames[][CAN_DLC], uint8_t frame_count,
                                   uint8_t *out_payload, uint16_t *out_len)
{
    uint16_t total_len;
    uint16_t written;
    uint8_t expected_sn = 1U;

    if ((frames == NULL) || (out_payload == NULL) || (out_len == NULL) || (frame_count == 0U)) {
        return -1;
    }
    if ((frames[0][0] >> 4) != 0x1U) {
        return -1;
    }

    total_len = (uint16_t)(((uint16_t)(frames[0][0] & 0x0FU) << 8) | frames[0][1]);
    if (total_len > MAX_PAYLOAD) {
        return -1;
    }

    written = (total_len < FF_DATA_BYTES) ? total_len : FF_DATA_BYTES;
    for (uint8_t i = 0U; i < written; i++) {
        out_payload[i] = frames[0][2U + i];
    }

    for (uint8_t f = 1U; f < frame_count; f++) {
        uint8_t pci_type = (uint8_t)(frames[f][0] >> 4);
        uint8_t sn;
        uint16_t remaining;
        uint8_t chunk;

        if (pci_type != 0x2U) {
            return -1;
        }

        sn = (uint8_t)(frames[f][0] & 0x0FU);
        if (sn != expected_sn) {
            printf("Error: expected SN=%u but got SN=%u at frame %u\n", expected_sn, sn, f);
            return -1;
        }

        remaining = (uint16_t)(total_len - written);
        chunk = (remaining >= CF_DATA_BYTES) ? CF_DATA_BYTES : (uint8_t)remaining;
        for (uint8_t i = 0U; i < chunk; i++) {
            out_payload[written + i] = frames[f][1U + i];
        }
        written = (uint16_t)(written + chunk);

        expected_sn = (uint8_t)((expected_sn + 1U) & 0x0FU);
        if (expected_sn == 0U) {
            expected_sn = 1U;
        }
    }

    if (written != total_len) {
        return -1;
    }

    *out_len = written;
    return 0;
}

int main(void)
{
    /* FF for a 20-byte payload (0x00..0x13), followed by two CFs. */
    uint8_t good_frames[3][CAN_DLC] = {
        {0x10U, 0x14U, 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U},
        {0x21U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU},
        {0x22U, 0x0DU, 0x0EU, 0x0FU, 0x10U, 0x11U, 0x12U, 0x13U},
    };
    /* Same message but the second CF has a corrupted SN (should be 2, but is 3). */
    uint8_t bad_frames[3][CAN_DLC] = {
        {0x10U, 0x14U, 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U},
        {0x21U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU},
        {0x23U, 0x0DU, 0x0EU, 0x0FU, 0x10U, 0x11U, 0x12U, 0x13U},
    };
    uint8_t payload[MAX_PAYLOAD];
    uint16_t len = 0U;

    if (reassemble_message(good_frames, 3U, payload, &len) == 0) {
        printf("Reassembled %u bytes:", len);
        for (uint16_t i = 0U; i < len; i++) {
            printf(" 0x%02X", payload[i]);
        }
        printf("\n");
    } else {
        printf("Unexpected failure on good stream\n");
    }

    if (reassemble_message(bad_frames, 3U, payload, &len) != 0) {
        printf("Correctly detected sequence error in corrupted stream\n");
    } else {
        printf("Missed the sequence error!\n");
    }

    return 0;
}
