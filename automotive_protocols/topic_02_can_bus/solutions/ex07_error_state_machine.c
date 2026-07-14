/*
 * ex07_error_state_machine.c - Model the CAN TEC/REC error counters and node states.
 * Key concept: Error Active (<128) -> Error Passive (128-255) -> Bus-Off (TEC>255), recovered after 128x11 recessive bits.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define CAN_ERROR_PASSIVE_THRESHOLD 128U
#define CAN_BUS_OFF_THRESHOLD       255U
#define CAN_BUS_OFF_RECOVERY_COUNT  128U

typedef enum {
    CAN_STATE_ERROR_ACTIVE = 0,
    CAN_STATE_ERROR_PASSIVE,
    CAN_STATE_BUS_OFF
} can_node_state_t;

typedef enum {
    CAN_EVT_TX_OK = 0,
    CAN_EVT_TX_ERROR,
    CAN_EVT_RX_OK,
    CAN_EVT_RX_ERROR
} can_event_t;

typedef struct {
    uint16_t         tec;
    uint16_t         rec;
    can_node_state_t state;
} can_node_t;

static const char *can_state_name(can_node_state_t state)
{
    switch (state) {
        case CAN_STATE_ERROR_ACTIVE:  return "ERROR_ACTIVE";
        case CAN_STATE_ERROR_PASSIVE: return "ERROR_PASSIVE";
        case CAN_STATE_BUS_OFF:       return "BUS_OFF";
        default:                      return "UNKNOWN";
    }
}

static void can_update_state(can_node_t *node)
{
    if (node == NULL) {
        return;
    }
    if (node->tec > CAN_BUS_OFF_THRESHOLD) {
        node->state = CAN_STATE_BUS_OFF;
    } else if ((node->tec >= CAN_ERROR_PASSIVE_THRESHOLD) || (node->rec >= CAN_ERROR_PASSIVE_THRESHOLD)) {
        node->state = CAN_STATE_ERROR_PASSIVE;
    } else {
        node->state = CAN_STATE_ERROR_ACTIVE;
    }
}

static void can_apply_event(can_node_t *node, can_event_t evt)
{
    if (node == NULL) {
        return;
    }
    switch (evt) {
        case CAN_EVT_TX_OK:
            if (node->tec > 0U) {
                node->tec--;
            }
            break;
        case CAN_EVT_TX_ERROR:
            node->tec = (uint16_t)(node->tec + 8U);
            break;
        case CAN_EVT_RX_OK:
            if (node->rec > 0U) {
                node->rec--;
            }
            break;
        case CAN_EVT_RX_ERROR:
            node->rec = (uint16_t)(node->rec + 8U);
            break;
        default:
            break;
    }
    can_update_state(node);
}

static uint32_t can_bus_off_recover(can_node_t *node)
{
    if (node == NULL) {
        return 0U;
    }
    uint32_t recessiveSequencesSeen = 0U;
    while (recessiveSequencesSeen < CAN_BUS_OFF_RECOVERY_COUNT) {
        recessiveSequencesSeen++; /* each iteration = 11 consecutive recessive bits observed */
    }
    node->tec   = 0U;
    node->rec   = 0U;
    node->state = CAN_STATE_ERROR_ACTIVE;
    return recessiveSequencesSeen;
}

int main(void)
{
    can_node_t node = { 0U, 0U, CAN_STATE_ERROR_ACTIVE };
    can_event_t stream[] = {
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR,
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR,
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR,
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR,
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR,
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR,
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR,
        CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR, CAN_EVT_TX_ERROR
    };
    size_t count = sizeof(stream) / sizeof(stream[0]);

    for (size_t i = 0U; i < count; i++) {
        can_apply_event(&node, stream[i]);
    }
    printf("After %zu TX errors: TEC=%u state=%s\n", count, node.tec, can_state_name(node.state));

    /* push past bus-off threshold */
    for (uint8_t i = 0U; i < 4U; i++) {
        can_apply_event(&node, CAN_EVT_TX_ERROR);
    }
    printf("After further errors: TEC=%u state=%s\n", node.tec, can_state_name(node.state));

    uint32_t seqs = can_bus_off_recover(&node);
    printf("Bus-off recovery observed %u x 11 recessive bits\n", seqs);
    printf("Post-recovery: TEC=%u REC=%u state=%s\n", node.tec, node.rec, can_state_name(node.state));

    return 0;
}
