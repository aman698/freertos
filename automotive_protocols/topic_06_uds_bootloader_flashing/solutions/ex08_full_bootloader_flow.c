/*
 * ex08_full_bootloader_flow.c - Chain the full UDS reflash state machine end to end.
 * Key concept: RequestDownload -> TransferData loop -> RequestTransferExit -> checkProgrammingDependencies -> ECUReset.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_ECU_RESET          0x11U
#define IMAGE_SIZE             40U
#define MAX_BLOCK_LEN          16U
#define DATA_PER_BLOCK         (MAX_BLOCK_LEN - 2U)
#define ROUTINE_ID_CHECK_DEPS  0xFF01U

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

static void requestDownload(uint32_t address, uint32_t size)
{
    printf("TX: 34 00 44 %08lX %08lX (RequestDownload)\n",
           (unsigned long)address, (unsigned long)size);
    printf("RX: 74 20 %04lX (maxNumberOfBlockLength)\n", (unsigned long)MAX_BLOCK_LEN);
}

static void transferDataLoop(const uint8_t *image, uint32_t len)
{
    uint8_t counter = 1U;
    uint32_t sent = 0U;

    if (image == NULL) {
        return;
    }

    while (sent < len) {
        uint32_t chunk = len - sent;

        if (chunk > DATA_PER_BLOCK) {
            chunk = DATA_PER_BLOCK;
        }

        printf("TX: 36 %02X <%lu bytes>\n", counter, (unsigned long)chunk);
        printf("RX: 76 %02X\n", counter);

        sent += chunk;
        counter++;
    }
}

static void requestTransferExit(uint32_t crc)
{
    printf("TX: 37 %08lX (final CRC)\n", (unsigned long)crc);
    printf("RX: 77\n");
}

static uint8_t checkProgrammingDependencies(uint32_t actualCrc, uint32_t expectedCrc, const char **reasonOut)
{
    if (reasonOut == NULL) {
        return 0U;
    }

    printf("TX: 31 01 %04lX (checkProgrammingDependencies)\n", (unsigned long)ROUTINE_ID_CHECK_DEPS);

    if (actualCrc != expectedCrc) {
        *reasonOut = "checksum mismatch";
        printf("RX: 7F 31 22 (conditionsNotCorrect - checksum mismatch)\n");
        return 0U;
    }

    *reasonOut = "OK";
    printf("RX: 71 01 %04lX (dependencies satisfied)\n", (unsigned long)ROUTINE_ID_CHECK_DEPS);
    return 1U;
}

static void ecuReset(void)
{
    printf("TX: %02X 01 (hardReset)\n", SID_ECU_RESET);
    printf("RX: 51 01\n");
}

static void runFlow(uint32_t expectedCrc)
{
    uint8_t image[IMAGE_SIZE];
    uint32_t actualCrc;
    const char *reason = NULL;

    for (uint32_t i = 0U; i < IMAGE_SIZE; i++) {
        image[i] = (uint8_t)(i + 1U);
    }
    actualCrc = crc32Compute(image, IMAGE_SIZE);

    requestDownload(0x08004000U, IMAGE_SIZE);
    transferDataLoop(image, IMAGE_SIZE);
    requestTransferExit(actualCrc);

    if (checkProgrammingDependencies(actualCrc, expectedCrc, &reason) != 0U) {
        printf("checkProgrammingDependencies: PASS (%s)\n", reason);
        ecuReset();
        printf("Flow result: SUCCESS - new application will boot\n");
    } else {
        printf("checkProgrammingDependencies: FAIL (%s) - ECUReset withheld\n", reason);
        printf("Flow result: ABORTED before ECUReset\n");
    }
}

int main(void)
{
    uint8_t image[IMAGE_SIZE];
    uint32_t realCrc;

    for (uint32_t i = 0U; i < IMAGE_SIZE; i++) {
        image[i] = (uint8_t)(i + 1U);
    }
    realCrc = crc32Compute(image, IMAGE_SIZE);

    printf("==== Run 1: matching CRC (expected success) ====\n");
    runFlow(realCrc);

    printf("\n==== Run 2: mismatched CRC (expected failure path) ====\n");
    runFlow(realCrc ^ 0x00000001U);

    return 0;
}
