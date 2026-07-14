/*
 * ex08_std_vs_extended_priority.c - Show that a standard frame beats an extended frame sharing the same base ID.
 * Key concept: after the base ID, IDE is dominant (0) for standard frames but the SRR bit is recessive (1) for extended.
 */
#include <stdint.h>
#include <stdio.h>

#define CAN_BASE_ID_BITS 11U

typedef struct {
    uint16_t baseId;
    uint8_t  isExtended; /* 0 = standard, 1 = extended */
} can_node_tx_t;

/* returns 0 if node A wins, 1 if node B wins, -1 if undecided after base ID */
static int32_t can_arbitrate_base_then_ide(const can_node_tx_t *a, const can_node_tx_t *b)
{
    for (int8_t bit = (int8_t)(CAN_BASE_ID_BITS - 1U); bit >= 0; bit--) {
        uint16_t bitA = (uint16_t)((a->baseId >> bit) & 1U);
        uint16_t bitB = (uint16_t)((b->baseId >> bit) & 1U);
        printf("  base bit%2d: A=%u B=%u\n", bit, bitA, bitB);
        if (bitA != bitB) {
            return (bitA == 0U) ? 0 : 1;
        }
    }

    /* base IDs identical: compare the bit immediately following it.
     * Standard frame sends IDE = 0 (dominant) here.
     * Extended frame sends SRR = 1 (recessive) here. */
    uint8_t nextBitA = a->isExtended ? 1U : 0U;
    uint8_t nextBitB = b->isExtended ? 1U : 0U;
    printf("  IDE/SRR bit: A=%u (%s) B=%u (%s)\n",
           nextBitA, a->isExtended ? "SRR" : "IDE",
           nextBitB, b->isExtended ? "SRR" : "IDE");

    if (nextBitA != nextBitB) {
        return (nextBitA == 0U) ? 0 : 1;
    }
    return -1;
}

int main(void)
{
    can_node_tx_t nodeStd = { 0x123U, 0U }; /* standard frame */
    can_node_tx_t nodeExt = { 0x123U, 1U }; /* extended frame, same base ID */

    printf("Same base ID 0x%03X: standard vs extended\n", nodeStd.baseId);
    int32_t winner = can_arbitrate_base_then_ide(&nodeStd, &nodeExt);

    if (winner == 0) {
        printf("Result: standard frame wins (IDE dominant beats SRR recessive)\n");
    } else if (winner == 1) {
        printf("Result: extended frame wins\n");
    } else {
        printf("Result: undecided\n");
    }
    return 0;
}
