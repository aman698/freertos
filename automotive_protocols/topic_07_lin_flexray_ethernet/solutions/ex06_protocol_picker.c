/*
 * ex06_protocol_picker.c - Pick the best-fit network for illustrative requirements.
 * Key concept: cost, determinism, and bandwidth needs point to different networks.
 */
#include <stddef.h>
#include <stdio.h>

typedef enum {
    REQ_COST_SENSITIVE_LOW_SPEED = 0,
    REQ_SAFETY_CRITICAL_DETERMINISTIC,
    REQ_HIGH_BANDWIDTH_STREAM,
    REQ_COUNT
} Requirement_t;

static void pick_network(Requirement_t req, const char **network_out, const char **reason_out)
{
    if ((network_out == NULL) || (reason_out == NULL)) {
        return;
    }
    switch (req) {
        case REQ_COST_SENSITIVE_LOW_SPEED:
            *network_out = "LIN";
            *reason_out = "single wire, cheap slave nodes, speed is not a concern";
            break;
        case REQ_SAFETY_CRITICAL_DETERMINISTIC:
            *network_out = "FlexRay";
            *reason_out = "TDMA static segment guarantees fixed, jitter-free timing";
            break;
        case REQ_HIGH_BANDWIDTH_STREAM:
            *network_out = "Automotive Ethernet";
            *reason_out = "100BASE-T1/1000BASE-T1 gives the throughput camera/video needs";
            break;
        default:
            *network_out = "CAN";
            *reason_out = "general-purpose default when no special constraint dominates";
            break;
    }
}

static const char *requirement_name(Requirement_t req)
{
    switch (req) {
        case REQ_COST_SENSITIVE_LOW_SPEED:      return "Cost-sensitive low-speed actuator";
        case REQ_SAFETY_CRITICAL_DETERMINISTIC: return "Safety-critical deterministic control";
        case REQ_HIGH_BANDWIDTH_STREAM:         return "High-bandwidth camera stream";
        default:                                return "Unknown";
    }
}

int main(void)
{
    for (unsigned int i = 0U; i < (unsigned int)REQ_COUNT; i++) {
        Requirement_t req = (Requirement_t)i;
        const char *network = NULL;
        const char *reason = NULL;

        pick_network(req, &network, &reason);
        printf("%-38s -> %-20s (%s)\n", requirement_name(req), network, reason);
    }

    return 0;
}
