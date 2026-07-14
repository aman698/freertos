/* ex05_stmin_encoding.c - Encode/decode ISO-TP STmin (minimum separation time) values. */
/* Key concept: 0x00-0x7F is ms, 0xF1-0xF9 is 100-900us, other ranges are reserved. */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define STMIN_MS_MAX      0x7FU
#define STMIN_US_LO       0xF1U
#define STMIN_US_HI       0xF9U

static int32_t stmin_encode_ms(uint8_t ms, uint8_t *out)
{
    if ((out == NULL) || (ms > STMIN_MS_MAX)) {
        return -1;
    }
    *out = ms;
    return 0;
}

static int32_t stmin_encode_100us_steps(uint8_t steps, uint8_t *out)
{
    if ((out == NULL) || (steps < 1U) || (steps > 9U)) {
        return -1;
    }
    *out = (uint8_t)(0xF0U + steps);
    return 0;
}

/* Decodes a raw STmin byte into a human-readable delay description. */
static int32_t stmin_decode(uint8_t raw, char *desc, size_t desc_len)
{
    if ((desc == NULL) || (desc_len == 0U)) {
        return -1;
    }

    if (raw <= STMIN_MS_MAX) {
        (void)snprintf(desc, desc_len, "%u ms", raw);
        return 0;
    }
    if ((raw >= STMIN_US_LO) && (raw <= STMIN_US_HI)) {
        (void)snprintf(desc, desc_len, "%u us", (unsigned)(raw - 0xF0U) * 100U);
        return 0;
    }

    (void)snprintf(desc, desc_len, "reserved");
    return -1;
}

int main(void)
{
    uint8_t byte_val = 0U;
    char desc[16];
    const uint8_t sample_raw[5] = {0x00U, 0x32U, 0x7FU, 0xF3U, 0x80U};

    if (stmin_encode_ms(50U, &byte_val) == 0) {
        printf("50 ms encodes to 0x%02X\n", byte_val);
    }

    if (stmin_encode_100us_steps(3U, &byte_val) == 0) {
        printf("300 us encodes to 0x%02X\n", byte_val);
    }

    for (uint8_t i = 0U; i < (uint8_t)sizeof(sample_raw); i++) {
        int32_t rc = stmin_decode(sample_raw[i], desc, sizeof(desc));
        printf("Raw 0x%02X -> %s%s\n", sample_raw[i], desc, (rc != 0) ? " (invalid)" : "");
    }

    return 0;
}
