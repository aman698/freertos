/*
 * ex10_multi_node_arbitration.c - Simulate simultaneous transmission by several CAN nodes.
 * Key concept: nodes drop out bit-by-bit whenever they drive recessive while another drives dominant.
 */
#include <stdint.h>
#include <stdio.h>

#define CAN_STD_ID_BITS 11U
#define NODE_COUNT      4U

typedef struct {
    const char *name;
    uint16_t    id;
    uint8_t     stillInContention;
} can_node_t;

static uint16_t can_dominant_bits(const can_node_t *nodes, uint8_t count, int8_t bit)
{
    /* dominant (0) wins on a shared bus if ANY contending node drives 0 */
    uint16_t anyDominant = 0U;
    for (uint8_t i = 0U; i < count; i++) {
        if (!nodes[i].stillInContention) {
            continue;
        }
        uint16_t b = (uint16_t)((nodes[i].id >> bit) & 1U);
        if (b == 0U) {
            anyDominant = 1U;
        }
    }
    return anyDominant;
}

int main(void)
{
    can_node_t nodes[NODE_COUNT] = {
        { "Node-A", 0x1A5U, 1U },
        { "Node-B", 0x1A3U, 1U },
        { "Node-C", 0x1FFU, 1U },
        { "Node-D", 0x1A3U, 1U }
    };

    printf("Nodes contending for the bus:\n");
    for (uint8_t i = 0U; i < NODE_COUNT; i++) {
        printf("  %s: ID=0x%03X\n", nodes[i].name, nodes[i].id);
    }

    printf("\nArbitration, bit by bit:\n");
    for (int8_t bit = (int8_t)(CAN_STD_ID_BITS - 1U); bit >= 0; bit--) {
        uint16_t busBit = can_dominant_bits(nodes, NODE_COUNT, bit);
        printf("  bit%2d: bus driven to %u -> ", bit, busBit);

        for (uint8_t i = 0U; i < NODE_COUNT; i++) {
            if (!nodes[i].stillInContention) {
                continue;
            }
            uint16_t myBit = (uint16_t)((nodes[i].id >> bit) & 1U);
            if (myBit != busBit) {
                nodes[i].stillInContention = 0U;
                printf("%s drops out; ", nodes[i].name);
            }
        }
        printf("\n");
    }

    printf("\nSurviving node(s) after arbitration:\n");
    for (uint8_t i = 0U; i < NODE_COUNT; i++) {
        if (nodes[i].stillInContention) {
            printf("  %s (ID=0x%03X) wins the bus\n", nodes[i].name, nodes[i].id);
        }
    }
    return 0;
}
