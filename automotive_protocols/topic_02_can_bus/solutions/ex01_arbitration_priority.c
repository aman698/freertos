/*
 * ex01_arbitration_priority.c - Compare two 11-bit CAN standard identifiers for bus arbitration.
 * Key concept: a dominant bit (0) always beats a recessive bit (1), so the numerically lower ID wins the bus.
 */
#include <stdint.h>
#include <stdio.h>

#define CAN_STD_ID_BITS 11U

static int32_t can_arbitrate_std_ids(uint16_t idA, uint16_t idB)
{
    for (int8_t bit = (int8_t)(CAN_STD_ID_BITS - 1U); bit >= 0; bit--) {
        uint16_t bitA = (uint16_t)((idA >> bit) & 1U);
        uint16_t bitB = (uint16_t)((idB >> bit) & 1U);

        printf("  bit%2d: A=%u B=%u\n", bit, bitA, bitB);

        if (bitA != bitB) {
            return (bitA == 0U) ? 0 : 1; /* dominant bit (0) wins the bus */
        }
    }
    return -1; /* identical IDs - would collide, undefined per spec */
}

static void can_print_id_bits(const char *label, uint16_t id)
{
    printf("%s = 0x%03X = ", label, id);
    for (int8_t bit = (int8_t)(CAN_STD_ID_BITS - 1U); bit >= 0; bit--) {
        putchar(((id >> bit) & 1U) ? '1' : '0');
    }
    putchar('\n');
}

int main(void)
{
    uint16_t idA = 0x100U;
    uint16_t idB = 0x105U;

    can_print_id_bits("Node A ID", idA);
    can_print_id_bits("Node B ID", idB);

    printf("Arbitration trace:\n");
    int32_t winner = can_arbitrate_std_ids(idA, idB);

    if (winner == 0) {
        printf("Result: Node A wins arbitration (lower ID = higher priority)\n");
    } else if (winner == 1) {
        printf("Result: Node B wins arbitration (lower ID = higher priority)\n");
    } else {
        printf("Result: identical IDs, arbitration undefined\n");
    }
    return 0;
}
