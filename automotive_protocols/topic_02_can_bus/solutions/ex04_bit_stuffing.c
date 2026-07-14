/*
 * ex04_bit_stuffing.c - Simulate CAN bit stuffing and de-stuffing.
 * Key concept: after 5 consecutive identical bits, CAN inserts one opposite bit to keep synchronization.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define STUFF_RUN_LEN 5U
#define MAX_BITS      64U

static size_t can_stuff_bits(const uint8_t *in, size_t inLen, uint8_t *out, size_t outCap)
{
    size_t  outLen   = 0U;
    uint8_t runBit   = 0xFFU; /* sentinel: no run yet */
    size_t  runCount = 0U;

    for (size_t i = 0U; i < inLen; i++) {
        if (outLen >= outCap) {
            break;
        }
        out[outLen++] = in[i];

        if (in[i] == runBit) {
            runCount++;
        } else {
            runBit   = in[i];
            runCount = 1U;
        }

        if (runCount == STUFF_RUN_LEN) {
            uint8_t stuffBit = (uint8_t)(runBit ^ 1U);
            if (outLen < outCap) {
                out[outLen++] = stuffBit;
            }
            runBit   = stuffBit;
            runCount = 1U;
        }
    }
    return outLen;
}

static size_t can_destuff_bits(const uint8_t *in, size_t inLen, uint8_t *out, size_t outCap)
{
    size_t  outLen   = 0U;
    uint8_t runBit   = 0xFFU; /* sentinel: no run yet */
    size_t  runCount = 0U;

    for (size_t i = 0U; i < inLen; i++) {
        if (runCount == STUFF_RUN_LEN) {
            /* in[i] is the stuff bit the sender inserted - drop it, restart run */
            runBit   = in[i];
            runCount = 1U;
            continue;
        }

        if (outLen < outCap) {
            out[outLen++] = in[i];
        }

        if (in[i] == runBit) {
            runCount++;
        } else {
            runBit   = in[i];
            runCount = 1U;
        }
    }
    return outLen;
}

static void can_print_bits(const char *label, const uint8_t *bits, size_t len)
{
    printf("%s (%zu bits): ", label, len);
    for (size_t i = 0U; i < len; i++) {
        putchar(bits[i] ? '1' : '0');
    }
    putchar('\n');
}

int main(void)
{
    uint8_t original[] = { 1U, 1U, 1U, 1U, 1U, 0U, 1U, 0U, 0U, 0U, 0U, 0U, 1U };
    size_t  originalLen = sizeof(original) / sizeof(original[0]);

    uint8_t stuffed[MAX_BITS];
    uint8_t destuffed[MAX_BITS];

    size_t stuffedLen   = can_stuff_bits(original, originalLen, stuffed, MAX_BITS);
    size_t destuffedLen = can_destuff_bits(stuffed, stuffedLen, destuffed, MAX_BITS);

    can_print_bits("Original ", original, originalLen);
    can_print_bits("Stuffed  ", stuffed, stuffedLen);
    can_print_bits("Destuffed", destuffed, destuffedLen);

    int match = (destuffedLen == originalLen);
    for (size_t i = 0U; match && (i < originalLen); i++) {
        if (destuffed[i] != original[i]) {
            match = 0;
        }
    }
    printf("De-stuffed matches original: %s\n", match ? "YES" : "NO");
    return 0;
}
