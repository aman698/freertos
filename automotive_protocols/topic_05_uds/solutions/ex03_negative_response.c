/*
 * ex03_negative_response.c - Build a generic 0x7F negative response and decode its NRC.
 * Key concept: negative response is always 0x7F + echoed SID + one NRC byte.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t code;
    const char *name;
} NrcEntry_t;

static const NrcEntry_t NRC_TABLE[] = {
    {0x10U, "generalReject"},
    {0x11U, "serviceNotSupported"},
    {0x12U, "subFunctionNotSupported"},
    {0x13U, "incorrectMessageLengthOrInvalidFormat"},
    {0x22U, "conditionsNotCorrect"},
    {0x24U, "requestSequenceError"},
    {0x31U, "requestOutOfRange"},
    {0x33U, "securityAccessDenied"},
    {0x35U, "invalidKey"},
    {0x36U, "exceedNumberOfAttempts"},
    {0x37U, "requiredTimeDelayNotExpired"},
    {0x78U, "requestCorrectlyReceived-ResponsePending"}
};

static const size_t NRC_TABLE_LEN = sizeof(NRC_TABLE) / sizeof(NRC_TABLE[0]);

static const char *nrc_to_string(uint8_t nrc)
{
    for (size_t i = 0U; i < NRC_TABLE_LEN; i++) {
        if (NRC_TABLE[i].code == nrc) {
            return NRC_TABLE[i].name;
        }
    }
    return "unknownNRC";
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

static void print_negative_response(const uint8_t *frame, size_t len)
{
    if ((frame == NULL) || (len < 3U)) {
        return;
    }
    printf("Frame: 0x%02X 0x%02X 0x%02X -> SID=0x%02X NRC=0x%02X (%s)\n",
           frame[0], frame[1], frame[2], frame[1], frame[2], nrc_to_string(frame[2]));
}

int main(void)
{
    uint8_t frame[3];
    uint8_t sample_sids[3] = {0x22U, 0x27U, 0x31U};
    uint8_t sample_nrcs[3] = {0x31U, 0x35U, 0x78U};

    for (size_t i = 0U; i < 3U; i++) {
        size_t len = build_negative_response(frame, sizeof(frame), sample_sids[i], sample_nrcs[i]);
        print_negative_response(frame, len);
    }

    return 0;
}
