/* ex10_end_to_end.c - End-to-end ISO-TP simulation: segment, flow-control, reassemble. */
/* Key concept: sender and receiver cooperate through FF, FC (BS/STmin), and CF frames. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC          8U
#define FF_DATA_BYTES    6U
#define CF_DATA_BYTES    7U
#define MAX_FRAMES      10U
#define UDS_LEN         30U

/* ---- Sender side: segmentation ---- */
static int32_t segment_message(const uint8_t *payload, uint16_t len,
                                uint8_t frames[][CAN_DLC], uint8_t max_frames,
                                uint8_t *frame_count_out)
{
    uint16_t remaining;
    uint16_t offset;
    uint8_t frame_idx;
    uint8_t sn = 1U;

    if ((payload == NULL) || (frames == NULL) || (frame_count_out == NULL) || (max_frames == 0U)) {
        return -1;
    }

    memset(frames[0], 0, CAN_DLC);
    frames[0][0] = (uint8_t)(0x10U | ((len >> 8) & 0x0FU));
    frames[0][1] = (uint8_t)(len & 0xFFU);
    for (uint8_t i = 0U; i < FF_DATA_BYTES; i++) {
        frames[0][2U + i] = (i < len) ? payload[i] : 0U;
    }
    frame_idx = 1U;

    offset = FF_DATA_BYTES;
    remaining = (len > FF_DATA_BYTES) ? (uint16_t)(len - FF_DATA_BYTES) : 0U;

    while (remaining > 0U) {
        uint8_t chunk = (remaining >= CF_DATA_BYTES) ? CF_DATA_BYTES : (uint8_t)remaining;

        if (frame_idx >= max_frames) {
            return -1;
        }

        memset(frames[frame_idx], 0, CAN_DLC);
        frames[frame_idx][0] = (uint8_t)(0x20U | (sn & 0x0FU));
        for (uint8_t i = 0U; i < chunk; i++) {
            frames[frame_idx][1U + i] = payload[offset + i];
        }

        offset = (uint16_t)(offset + chunk);
        remaining = (uint16_t)(remaining - chunk);
        sn = (uint8_t)((sn + 1U) & 0x0FU);
        if (sn == 0U) {
            sn = 1U;
        }
        frame_idx++;
    }

    *frame_count_out = frame_idx;
    return 0;
}

/* ---- Receiver side: reassembly ---- */
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
    written = (total_len < FF_DATA_BYTES) ? total_len : FF_DATA_BYTES;
    for (uint8_t i = 0U; i < written; i++) {
        out_payload[i] = frames[0][2U + i];
    }

    for (uint8_t f = 1U; f < frame_count; f++) {
        uint8_t sn = (uint8_t)(frames[f][0] & 0x0FU);
        uint16_t remaining = (uint16_t)(total_len - written);
        uint8_t chunk = (remaining >= CF_DATA_BYTES) ? CF_DATA_BYTES : (uint8_t)remaining;

        if ((frames[f][0] >> 4) != 0x2U) {
            return -1;
        }
        if (sn != expected_sn) {
            return -1;
        }

        for (uint8_t i = 0U; i < chunk; i++) {
            out_payload[written + i] = frames[f][1U + i];
        }
        written = (uint16_t)(written + chunk);

        expected_sn = (uint8_t)((expected_sn + 1U) & 0x0FU);
        if (expected_sn == 0U) {
            expected_sn = 1U;
        }
    }

    *out_len = written;
    return (written == total_len) ? 0 : -1;
}

int main(void)
{
    /* Simulated UDS-like response payload (e.g. ReadDataByIdentifier). */
    uint8_t uds_payload[UDS_LEN];
    uint8_t frames[MAX_FRAMES][CAN_DLC];
    uint8_t frame_count = 0U;
    uint8_t bs = 3U;
    uint8_t stmin = 0x0AU;
    uint8_t sent_since_fc;
    uint8_t rebuilt[UDS_LEN];
    uint16_t rebuilt_len = 0U;

    for (uint8_t i = 0U; i < UDS_LEN; i++) {
        uds_payload[i] = (uint8_t)(0x62U + i);
    }

    if (segment_message(uds_payload, UDS_LEN, frames, MAX_FRAMES, &frame_count) != 0) {
        printf("Segmentation failed\n");
        return 0;
    }
    printf("Segmented %u-byte UDS payload into %u frames\n", UDS_LEN, frame_count);

    printf("Sender -> Transmit FF: 0x%02X 0x%02X ...\n", frames[0][0], frames[0][1]);
    printf("Receiver -> FC: FS=Continue To Send, BS=%u, STmin=0x%02X\n", bs, stmin);

    sent_since_fc = 0U;
    for (uint8_t f = 1U; f < frame_count; f++) {
        printf("Sender -> CF SN=%u\n", (uint8_t)(frames[f][0] & 0x0FU));
        sent_since_fc++;
        if ((bs != 0U) && (sent_since_fc == bs) && ((f + 1U) < frame_count)) {
            printf("Sender pauses (BS=%u reached), Receiver -> FC: Continue To Send\n", bs);
            sent_since_fc = 0U;
        }
    }

    if (reassemble_message(frames, frame_count, rebuilt, &rebuilt_len) != 0) {
        printf("Result: FAIL (reassembly error)\n");
        return 0;
    }

    if ((rebuilt_len == UDS_LEN) && (memcmp(rebuilt, uds_payload, UDS_LEN) == 0)) {
        printf("Result: PASS (%u bytes reconstructed correctly)\n", rebuilt_len);
    } else {
        printf("Result: FAIL (payload mismatch)\n");
    }

    return 0;
}
