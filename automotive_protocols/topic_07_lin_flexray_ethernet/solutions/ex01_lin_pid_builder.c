/*
 * ex01_lin_pid_builder.c - Build and verify a LIN Protected Identifier (PID).
 * Key concept: PID packs a 6-bit frame ID with 2 parity bits per the LIN parity formula.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint8_t lin_parity_p0(uint8_t id)
{
    uint8_t id0 = (uint8_t)((id >> 0) & 0x01U);
    uint8_t id1 = (uint8_t)((id >> 1) & 0x01U);
    uint8_t id2 = (uint8_t)((id >> 2) & 0x01U);
    uint8_t id4 = (uint8_t)((id >> 4) & 0x01U);
    return (uint8_t)(id0 ^ id1 ^ id2 ^ id4);
}

static uint8_t lin_parity_p1(uint8_t id)
{
    uint8_t id1 = (uint8_t)((id >> 1) & 0x01U);
    uint8_t id3 = (uint8_t)((id >> 3) & 0x01U);
    uint8_t id4 = (uint8_t)((id >> 4) & 0x01U);
    uint8_t id5 = (uint8_t)((id >> 5) & 0x01U);
    return (uint8_t)(~(id1 ^ id3 ^ id4 ^ id5) & 0x01U);
}

static uint8_t lin_build_pid(uint8_t frame_id)
{
    uint8_t id = (uint8_t)(frame_id & 0x3FU);
    uint8_t p0 = lin_parity_p0(id);
    uint8_t p1 = lin_parity_p1(id);
    return (uint8_t)(id | (uint8_t)(p0 << 6) | (uint8_t)(p1 << 7));
}

static int lin_verify_pid(uint8_t pid, uint8_t *decoded_id)
{
    if (decoded_id == NULL) {
        return 0;
    }
    uint8_t id = (uint8_t)(pid & 0x3FU);
    uint8_t recv_p0 = (uint8_t)((pid >> 6) & 0x01U);
    uint8_t recv_p1 = (uint8_t)((pid >> 7) & 0x01U);

    *decoded_id = id;
    return (recv_p0 == lin_parity_p0(id)) && (recv_p1 == lin_parity_p1(id));
}

int main(void)
{
    uint8_t frame_ids[] = {0x00U, 0x01U, 0x20U, 0x3FU};
    size_t count = sizeof(frame_ids) / sizeof(frame_ids[0]);

    for (size_t i = 0U; i < count; i++) {
        uint8_t pid = lin_build_pid(frame_ids[i]);
        uint8_t decoded_id = 0U;
        int ok = lin_verify_pid(pid, &decoded_id);

        printf("Frame ID 0x%02X -> PID 0x%02X | decoded ID 0x%02X | parity %s\n",
               frame_ids[i], pid, decoded_id, ok != 0 ? "OK" : "FAIL");
    }

    /* Corrupt one parity bit to demonstrate detection */
    uint8_t corrupt_pid = (uint8_t)(lin_build_pid(0x10U) ^ 0x40U);
    uint8_t decoded_id = 0U;
    int ok = lin_verify_pid(corrupt_pid, &decoded_id);

    printf("Corrupted PID 0x%02X -> decoded ID 0x%02X | parity %s\n",
           corrupt_pid, decoded_id, ok != 0 ? "OK" : "FAIL");

    return 0;
}
