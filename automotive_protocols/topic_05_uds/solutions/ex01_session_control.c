/*
 * ex01_session_control.c - Build DiagnosticSessionControl (0x10) request/response frames.
 * Key concept: positive response = SID+0x40 plus session parameter timing bytes.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_DIAGNOSTIC_SESSION_CONTROL 0x10U
#define NRC_SUB_FUNCTION_NOT_SUPPORTED 0x12U

typedef enum {
    SESSION_DEFAULT     = 0x01U,
    SESSION_PROGRAMMING = 0x02U,
    SESSION_EXTENDED    = 0x03U
} SessionType_t;

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

static size_t build_request(uint8_t *out, size_t cap, SessionType_t session)
{
    if ((out == NULL) || (cap < 2U)) {
        return 0U;
    }
    out[0] = SID_DIAGNOSTIC_SESSION_CONTROL;
    out[1] = (uint8_t)session;
    return 2U;
}

static size_t build_positive_response(uint8_t *out, size_t cap, SessionType_t session,
                                       uint16_t p2_ms, uint16_t p2_star_10ms)
{
    if ((out == NULL) || (cap < 6U)) {
        return 0U;
    }
    out[0] = SID_DIAGNOSTIC_SESSION_CONTROL + 0x40U;
    out[1] = (uint8_t)session;
    out[2] = (uint8_t)(p2_ms >> 8);
    out[3] = (uint8_t)(p2_ms & 0xFFU);
    out[4] = (uint8_t)(p2_star_10ms >> 8);
    out[5] = (uint8_t)(p2_star_10ms & 0xFFU);
    return 6U;
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
    size_t len;

    len = build_request(frame, sizeof(frame), SESSION_EXTENDED);
    print_frame("Request", frame, len);

    len = build_positive_response(frame, sizeof(frame), SESSION_EXTENDED, 50U, 500U);
    print_frame("Positive response", frame, len);

    len = build_negative_response(frame, sizeof(frame), SID_DIAGNOSTIC_SESSION_CONTROL,
                                   NRC_SUB_FUNCTION_NOT_SUPPORTED);
    print_frame("Negative response", frame, len);

    return 0;
}
