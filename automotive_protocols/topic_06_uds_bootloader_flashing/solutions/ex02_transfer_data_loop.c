/*
 * ex02_transfer_data_loop.c - Simulate a UDS TransferData (0x36) block loop.
 * Key concept: block sequence counter starts at 1 and wraps 0x00..0xFF.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_TRANSFER_DATA       0x36U
#define SID_TRANSFER_DATA_RESP  0x76U
#define NRC_REQUEST_SEQ_ERROR   0x24U
#define IMAGE_SIZE              300U
#define MAX_BLOCK_LEN           64U
#define DATA_PER_BLOCK          (MAX_BLOCK_LEN - 2U)

typedef struct {
    uint8_t expectedCounter;
    uint8_t initialized;
} TransferState_t;

static uint8_t receiveBlock(TransferState_t *state, uint8_t counter, uint32_t chunkLen, uint8_t *nrcOut)
{
    if ((state == NULL) || (nrcOut == NULL)) {
        return 0U;
    }

    *nrcOut = 0U;

    if (state->initialized == 0U) {
        state->expectedCounter = 1U;
        state->initialized = 1U;
    }

    if (counter != state->expectedCounter) {
        *nrcOut = NRC_REQUEST_SEQ_ERROR;
        return 0U;
    }

    state->expectedCounter = (uint8_t)(state->expectedCounter + 1U);
    (void)chunkLen;
    return 1U;
}

int main(void)
{
    uint8_t image[IMAGE_SIZE];
    TransferState_t state = {0U, 0U};
    uint32_t sent = 0U;
    uint8_t counter = 1U;
    uint8_t blockIndex = 0U;

    for (uint32_t i = 0U; i < IMAGE_SIZE; i++) {
        image[i] = (uint8_t)(i & 0xFFU);
    }

    while (sent < IMAGE_SIZE) {
        uint32_t chunk = IMAGE_SIZE - sent;
        uint8_t txCounter = counter;
        uint8_t nrc = 0U;

        if (chunk > DATA_PER_BLOCK) {
            chunk = DATA_PER_BLOCK;
        }

        blockIndex++;

        /* Inject an out-of-sequence counter on the 4th block to demonstrate rejection. */
        if (blockIndex == 4U) {
            txCounter = (uint8_t)(counter + 1U);
        }

        printf("TX: 36 %02X <%lu data bytes>\n", txCounter, (unsigned long)chunk);

        if (receiveBlock(&state, txCounter, chunk, &nrc) != 0U) {
            printf("RX: 76 %02X (accepted)\n", txCounter);
            sent += chunk;
            counter++;
        } else {
            printf("RX: 7F 36 %02X (NRC requestSequenceError - transfer aborted)\n", nrc);
            printf("Recovery: tester must restart from RequestDownload (0x34)\n");
            break;
        }
    }

    printf("Bytes transferred before stop: %lu of %lu\n",
           (unsigned long)sent, (unsigned long)IMAGE_SIZE);

    return 0;
}
