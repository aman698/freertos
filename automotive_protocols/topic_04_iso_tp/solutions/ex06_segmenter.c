/* ex06_segmenter.c - Segment a payload larger than 7 bytes into FF + CF frames. */
/* Key concept: one First Frame (6 bytes) followed by Consecutive Frames (7 bytes each). */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC          8U
#define FF_DATA_BYTES    6U
#define CF_DATA_BYTES    7U
#define MAX_FRAMES        8U

static int32_t segment_message(const uint8_t *payload, uint16_t len,
                                uint8_t frames[][CAN_DLC], uint8_t max_frames,
                                uint8_t *frame_count_out)
{
    uint16_t remaining;
    uint16_t offset;
    uint8_t frame_idx = 0U;
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

int main(void)
{
    uint8_t payload[20];
    uint8_t frames[MAX_FRAMES][CAN_DLC];
    uint8_t frame_count = 0U;

    for (uint8_t i = 0U; i < (uint8_t)sizeof(payload); i++) {
        payload[i] = i;
    }

    if (segment_message(payload, (uint16_t)sizeof(payload), frames, MAX_FRAMES, &frame_count) != 0) {
        printf("segmentation failed\n");
        return 0;
    }

    printf("Segmented %u-byte payload into %u frames\n", (unsigned)sizeof(payload), frame_count);
    for (uint8_t f = 0U; f < frame_count; f++) {
        printf("Frame %u:", f);
        for (uint8_t i = 0U; i < CAN_DLC; i++) {
            printf(" 0x%02X", frames[f][i]);
        }
        printf("\n");
    }

    return 0;
}
