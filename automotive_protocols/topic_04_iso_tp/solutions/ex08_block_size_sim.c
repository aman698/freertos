/* ex08_block_size_sim.c - Simulate a Flow Control block-size (BS) pacing sender. */
/* Key concept: BS>0 forces a pause for a new FC after every BS CFs; BS==0 sends all CFs. */
#include <stdint.h>
#include <stdio.h>

#define CF_DATA_BYTES    7U

/* Simulates sending consecutive frames for a payload, honoring the given block size.
 * Returns the number of Flow Control waits that occurred. */
static uint32_t send_with_block_size(uint16_t remaining_bytes, uint8_t bs)
{
    uint8_t sn = 1U;
    uint8_t sent_in_block = 0U;
    uint32_t fc_waits = 0U;

    while (remaining_bytes > 0U) {
        uint8_t chunk = (remaining_bytes >= CF_DATA_BYTES) ? CF_DATA_BYTES : (uint8_t)remaining_bytes;

        printf("  Sent CF SN=%u (%u bytes)\n", sn, chunk);
        remaining_bytes = (uint16_t)(remaining_bytes - chunk);
        sn = (uint8_t)((sn + 1U) & 0x0FU);
        if (sn == 0U) {
            sn = 1U;
        }
        sent_in_block++;

        if ((bs != 0U) && (sent_in_block == bs) && (remaining_bytes > 0U)) {
            printf("  Block limit (BS=%u) reached, waiting for Flow Control...\n", bs);
            printf("  Received FC: Continue To Send\n");
            fc_waits++;
            sent_in_block = 0U;
        }
    }

    return fc_waits;
}

int main(void)
{
    printf("Case 1: 30 bytes remaining, BS=2\n");
    (void)send_with_block_size(30U, 2U);

    printf("\nCase 2: 30 bytes remaining, BS=0 (send all without pausing)\n");
    uint32_t waits = send_with_block_size(30U, 0U);
    printf("  FC waits required: %u\n", waits);

    return 0;
}
