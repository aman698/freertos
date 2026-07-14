/*
 * ex09_remote_vs_data_frame.c - Simulate a remote-frame request answered by a data-frame response.
 * Key concept: RTR=1 (recessive) requests data; RTR=0 (dominant) data frame wins if it contends with a same-ID remote frame.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t id;
    uint8_t  rtr; /* 0 = data frame, 1 = remote frame */
    uint8_t  dlc;
    uint8_t  data[8];
} can_frame_t;

static can_frame_t can_make_remote_request(uint16_t id, uint8_t requestedLen)
{
    can_frame_t f = {0};
    f.id  = id;
    f.rtr = 1U;
    f.dlc = requestedLen;
    return f;
}

static can_frame_t can_make_data_response(uint16_t id, const uint8_t *data, uint8_t len)
{
    can_frame_t f = {0};
    f.id  = id;
    f.rtr = 0U;
    f.dlc = len;
    for (uint8_t i = 0U; i < len; i++) {
        f.data[i] = data[i];
    }
    return f;
}

static int32_t can_arbitrate_rtr(uint8_t rtrA, uint8_t rtrB)
{
    /* RTR dominant (0, data frame) beats RTR recessive (1, remote frame) */
    if (rtrA == rtrB) {
        return -1;
    }
    return (rtrA == 0U) ? 0 : 1;
}

int main(void)
{
    /* Node X requests sensor data with ID 0x300 */
    can_frame_t request = can_make_remote_request(0x300U, 4U);
    printf("Node X sends remote frame: ID=0x%03X RTR=%u DLC=%u (no data)\n",
           request.id, request.rtr, request.dlc);

    /* Node Y later answers with the actual data frame, same ID */
    uint8_t sensorData[4] = { 0x0AU, 0x0BU, 0x0CU, 0x0DU };
    can_frame_t response = can_make_data_response(0x300U, sensorData, 4U);

    printf("Node Y responds with data frame: ID=0x%03X RTR=%u DLC=%u DATA=[",
           response.id, response.rtr, response.dlc);
    for (uint8_t i = 0U; i < response.dlc; i++) {
        printf("0x%02X%s", response.data[i], ((uint8_t)(i + 1U) < response.dlc) ? " " : "");
    }
    printf("]\n");

    /* If both were transmitted at the same instant with the same ID,
     * arbitration on the RTR bit decides who continues. */
    int32_t winner = can_arbitrate_rtr(response.rtr, request.rtr);
    printf("\nIf simultaneous with same ID: %s wins arbitration (RTR dominant)\n",
           (winner == 0) ? "data frame (Node Y)" : "remote frame (Node X)");

    return 0;
}
