/*
 * ex03_frame_struct_builder.c - Build a CAN frame struct and pretty-print its fields.
 * Key concept: a CAN frame carries ID, IDE, RTR, DLC (0-8), and up to 8 data bytes.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define CAN_MAX_DLC 8U

typedef struct {
    uint32_t id;
    uint8_t  ide;               /* 0 = standard 11-bit, 1 = extended 29-bit */
    uint8_t  rtr;               /* 0 = data frame, 1 = remote frame */
    uint8_t  dlc;               /* 0..8 data length code */
    uint8_t  data[CAN_MAX_DLC];
} can_frame_t;

static can_frame_t can_build_frame(uint32_t id, uint8_t ide, uint8_t rtr,
                                    const uint8_t *payload, uint8_t len)
{
    can_frame_t frame = {0};
    frame.id  = id;
    frame.ide = ide;
    frame.rtr = rtr;
    frame.dlc = (len > CAN_MAX_DLC) ? CAN_MAX_DLC : len;

    for (uint8_t i = 0U; i < frame.dlc; i++) {
        frame.data[i] = (payload != NULL) ? payload[i] : 0U;
    }
    return frame;
}

static void can_print_frame(const can_frame_t *frame)
{
    if (frame == NULL) {
        return;
    }
    printf("ID=0x%03lX IDE=%u RTR=%u DLC=%u DATA=[",
           (unsigned long)frame->id, frame->ide, frame->rtr, frame->dlc);

    for (uint8_t i = 0U; i < frame->dlc; i++) {
        printf("0x%02X%s", frame->data[i], ((uint8_t)(i + 1U) < frame->dlc) ? " " : "");
    }
    printf("]\n");
}

int main(void)
{
    uint8_t payload[CAN_MAX_DLC] = { 0x11U, 0x22U, 0x33U, 0x44U };

    can_frame_t frame = can_build_frame(0x123U, 0U, 0U, payload, 4U);
    can_print_frame(&frame);

    can_frame_t remoteFrame = can_build_frame(0x200U, 0U, 1U, NULL, 0U);
    can_print_frame(&remoteFrame);

    return 0;
}
