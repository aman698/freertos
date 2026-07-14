/*
 * ex11_canfd_dlc_lookup.c - Map a 4-bit DLC code to payload length for classic CAN and CAN FD.
 * Key concept: classic CAN caps DLC at 8 bytes; CAN FD extends codes 9-15 to 12/16/20/24/32/48/64 bytes.
 */
#include <stdint.h>
#include <stdio.h>

#define DLC_CODE_COUNT 16U

static const uint8_t canFdLengthTable[DLC_CODE_COUNT] = {
    0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U,   /* DLC 0-8: same as classic CAN */
    12U, 16U, 20U, 24U, 32U, 48U, 64U     /* DLC 9-15: CAN FD only */
};

static uint8_t can_classic_length(uint8_t dlc)
{
    uint8_t clamped = (dlc > 8U) ? 8U : dlc;
    return clamped;
}

static uint8_t can_fd_length(uint8_t dlc)
{
    uint8_t idx = (dlc >= DLC_CODE_COUNT) ? (uint8_t)(DLC_CODE_COUNT - 1U) : dlc;
    return canFdLengthTable[idx];
}

int main(void)
{
    printf("%-4s %-14s %-10s\n", "DLC", "Classic bytes", "FD bytes");
    for (uint8_t dlc = 0U; dlc < DLC_CODE_COUNT; dlc++) {
        printf("%-4u %-14u %-10u\n", dlc, can_classic_length(dlc), can_fd_length(dlc));
    }

    printf("\nCAN FD adds BRS (Bit Rate Switch): data phase can run at a higher bit rate\n");
    printf("than the arbitration phase once arbitration has been won.\n");
    return 0;
}
