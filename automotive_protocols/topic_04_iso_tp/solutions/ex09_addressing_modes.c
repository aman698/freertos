/* ex09_addressing_modes.c - Compare normal vs extended ISO-TP addressing capacity. */
/* Key concept: extended addressing spends data byte 0 on a target address extension. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC              8U
#define TA_EXTENSION         0x5AU

typedef enum {
    ADDR_NORMAL = 0,
    ADDR_EXTENDED = 1
} addressing_mode_t;

/* Returns the number of usable payload bytes for a Single Frame under the given mode. */
static uint8_t sf_capacity(addressing_mode_t mode)
{
    return (mode == ADDR_NORMAL) ? 7U : 6U;
}

static uint8_t ff_capacity(addressing_mode_t mode)
{
    return (mode == ADDR_NORMAL) ? 6U : 5U;
}

static uint8_t cf_capacity(addressing_mode_t mode)
{
    return (mode == ADDR_NORMAL) ? 7U : 6U;
}

static int32_t build_sf(uint8_t *frame, addressing_mode_t mode, const uint8_t *payload, uint8_t len)
{
    uint8_t offset;

    if ((frame == NULL) || (payload == NULL) || (len > sf_capacity(mode))) {
        return -1;
    }

    memset(frame, 0, CAN_DLC);
    offset = 0U;
    if (mode == ADDR_EXTENDED) {
        frame[0] = TA_EXTENSION;
        offset = 1U;
    }
    frame[offset] = (uint8_t)(0x00U | len);
    for (uint8_t i = 0U; i < len; i++) {
        frame[offset + 1U + i] = payload[i];
    }
    return 0;
}

int main(void)
{
    const uint8_t payload[6] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U};
    uint8_t frame_normal[CAN_DLC];
    uint8_t frame_extended[CAN_DLC];

    printf("Normal addressing   : SF=%u CF=%u FF-first=%u bytes/frame\n",
           sf_capacity(ADDR_NORMAL), cf_capacity(ADDR_NORMAL), ff_capacity(ADDR_NORMAL));
    printf("Extended addressing : SF=%u CF=%u FF-first=%u bytes/frame\n",
           sf_capacity(ADDR_EXTENDED), cf_capacity(ADDR_EXTENDED), ff_capacity(ADDR_EXTENDED));

    if (build_sf(frame_normal, ADDR_NORMAL, payload, 6U) == 0) {
        printf("Normal SF (6 bytes fit):");
        for (uint8_t i = 0U; i < CAN_DLC; i++) {
            printf(" 0x%02X", frame_normal[i]);
        }
        printf("\n");
    }

    if (build_sf(frame_extended, ADDR_EXTENDED, payload, 6U) == 0) {
        printf("Extended SF (6 bytes fit): unexpected success\n");
    } else {
        printf("Extended SF with 6 bytes correctly rejected (only %u fit)\n",
               sf_capacity(ADDR_EXTENDED));
    }

    if (build_sf(frame_extended, ADDR_EXTENDED, payload, 5U) == 0) {
        printf("Extended SF (5 bytes fit):");
        for (uint8_t i = 0U; i < CAN_DLC; i++) {
            printf(" 0x%02X", frame_extended[i]);
        }
        printf("\n");
    }

    return 0;
}
