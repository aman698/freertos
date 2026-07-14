/*
 * ex04_checksum_validation.c - Validate a flashed image against an expected CRC32.
 * Key concept: CRC32 over the reassembled image is the final gate before acceptance.
 */
#include <stdint.h>
#include <stdio.h>

static uint32_t crc32Compute(const uint8_t *data, uint32_t len)
{
    uint32_t crc = 0xFFFFFFFFU;

    if (data == NULL) {
        return 0U;
    }

    for (uint32_t i = 0U; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 0U; bit < 8U; bit++) {
            if ((crc & 1U) != 0U) {
                crc = (crc >> 1) ^ 0xEDB88320U;
            } else {
                crc = crc >> 1;
            }
        }
    }

    return ~crc;
}

static uint8_t validateImage(const uint8_t *image, uint32_t len, uint32_t expectedCrc, uint32_t *actualCrcOut)
{
    if ((image == NULL) || (actualCrcOut == NULL)) {
        return 0U;
    }

    *actualCrcOut = crc32Compute(image, len);
    return (*actualCrcOut == expectedCrc) ? 1U : 0U;
}

int main(void)
{
    uint8_t image[16];
    uint32_t actual = 0U;
    uint32_t expectedGood;
    uint32_t expectedBad;

    for (uint32_t i = 0U; i < sizeof(image); i++) {
        image[i] = (uint8_t)(i * 3U);
    }

    expectedGood = crc32Compute(image, sizeof(image));
    expectedBad = expectedGood ^ 0x00000001U;

    if (validateImage(image, sizeof(image), expectedGood, &actual) != 0U) {
        printf("Image CRC = 0x%08lX, expected = 0x%08lX -> PASS\n",
               (unsigned long)actual, (unsigned long)expectedGood);
    } else {
        printf("Image CRC = 0x%08lX, expected = 0x%08lX -> FAIL\n",
               (unsigned long)actual, (unsigned long)expectedGood);
    }

    if (validateImage(image, sizeof(image), expectedBad, &actual) != 0U) {
        printf("Image CRC = 0x%08lX, expected = 0x%08lX -> PASS\n",
               (unsigned long)actual, (unsigned long)expectedBad);
    } else {
        printf("Image CRC = 0x%08lX, expected = 0x%08lX -> FAIL\n",
               (unsigned long)actual, (unsigned long)expectedBad);
    }

    return 0;
}
