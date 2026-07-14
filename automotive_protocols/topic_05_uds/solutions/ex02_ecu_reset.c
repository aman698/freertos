/*
 * ex02_ecu_reset.c - Build ECUReset (0x11) request/response for each reset type.
 * Key concept: sub-function selects hard/key-off-on/soft reset behavior.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_ECU_RESET 0x11U
#define NRC_SUB_FUNCTION_NOT_SUPPORTED 0x12U

typedef enum {
    RESET_HARD        = 0x01U,
    RESET_KEY_OFF_ON  = 0x02U,
    RESET_SOFT        = 0x03U
} ResetType_t;

static const char *reset_type_name(ResetType_t type)
{
    switch (type) {
        case RESET_HARD:       return "hardReset";
        case RESET_KEY_OFF_ON: return "keyOffOnReset";
        case RESET_SOFT:       return "softReset";
        default:               return "unknown";
    }
}

static void print_frame(const char *label, const uint8_t *frame, size_t len)
{
    if ((label == NULL) || (frame == NULL)) {
        return;
    }
    printf("%-18s:", label);
    for (size_t i = 0U; i < len; i++) {
        printf(" 0x%02X", frame[i]);
    }
    printf("\n");
}

static size_t build_request(uint8_t *out, size_t cap, ResetType_t type)
{
    if ((out == NULL) || (cap < 2U)) {
        return 0U;
    }
    out[0] = SID_ECU_RESET;
    out[1] = (uint8_t)type;
    return 2U;
}

static size_t build_positive_response(uint8_t *out, size_t cap, ResetType_t type)
{
    if ((out == NULL) || (cap < 2U)) {
        return 0U;
    }
    out[0] = SID_ECU_RESET + 0x40U;
    out[1] = (uint8_t)type;
    return 2U;
}

static size_t build_negative_response(uint8_t *out, size_t cap, uint8_t sid, uint8_t nrc)
{
    if ((out == NULL) || (cap < 3U)) {
        return 0U;
    }
    out[0] = 0x7FU;
    out[1] = sid;
    out[2] = nrc;
    return 3U;
}

int main(void)
{
    uint8_t frame[8];
    ResetType_t types[3] = {RESET_HARD, RESET_KEY_OFF_ON, RESET_SOFT};

    for (size_t i = 0U; i < 3U; i++) {
        size_t len = build_request(frame, sizeof(frame), types[i]);
        printf("-- %s --\n", reset_type_name(types[i]));
        print_frame("Request", frame, len);
        len = build_positive_response(frame, sizeof(frame), types[i]);
        print_frame("Positive response", frame, len);
    }

    size_t len = build_negative_response(frame, sizeof(frame), SID_ECU_RESET,
                                          NRC_SUB_FUNCTION_NOT_SUPPORTED);
    print_frame("Negative response", frame, len);

    return 0;
}
