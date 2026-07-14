/*
 * ex03_request_transfer_exit.c - Build and parse UDS RequestTransferExit (0x37).
 * Key concept: an optional parameter record can carry a final CRC to the ECU.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_TRANSFER_EXIT       0x37U
#define SID_TRANSFER_EXIT_RESP  0x77U
#define CRC_PARAM_LEN           4U

typedef struct {
    uint8_t  hasCrcParam;
    uint32_t crc32;
} TransferExitReq_t;

static uint32_t buildRequest(const TransferExitReq_t *req, uint8_t *out, uint32_t outCap)
{
    uint32_t idx = 0U;
    uint32_t needed;

    if ((req == NULL) || (out == NULL)) {
        return 0U;
    }

    needed = 1U + ((req->hasCrcParam != 0U) ? CRC_PARAM_LEN : 0U);
    if (outCap < needed) {
        return 0U;
    }

    out[idx] = SID_TRANSFER_EXIT;
    idx++;

    if (req->hasCrcParam != 0U) {
        out[idx] = (uint8_t)((req->crc32 >> 24) & 0xFFU);
        idx++;
        out[idx] = (uint8_t)((req->crc32 >> 16) & 0xFFU);
        idx++;
        out[idx] = (uint8_t)((req->crc32 >> 8) & 0xFFU);
        idx++;
        out[idx] = (uint8_t)(req->crc32 & 0xFFU);
        idx++;
    }

    return idx;
}

static uint8_t parseResponse(const uint8_t *resp, uint32_t len, uint32_t *echoedCrcOut)
{
    if ((resp == NULL) || (echoedCrcOut == NULL) || (len < 1U)) {
        return 0U;
    }
    if (resp[0] != SID_TRANSFER_EXIT_RESP) {
        return 0U;
    }

    *echoedCrcOut = 0U;
    if (len >= (1U + CRC_PARAM_LEN)) {
        *echoedCrcOut = ((uint32_t)resp[1] << 24) | ((uint32_t)resp[2] << 16) |
                        ((uint32_t)resp[3] << 8) | (uint32_t)resp[4];
    }

    return 1U;
}

static void printBytes(const char *label, const uint8_t *bytes, uint32_t len)
{
    if ((label == NULL) || (bytes == NULL)) {
        return;
    }
    printf("%s:", label);
    for (uint32_t i = 0U; i < len; i++) {
        printf(" 0x%02X", bytes[i]);
    }
    printf("\n");
}

int main(void)
{
    uint8_t buf[8];
    TransferExitReq_t withCrc = {1U, 0xDEADBEEFU};
    TransferExitReq_t noCrc = {0U, 0U};
    uint8_t resp[8] = {SID_TRANSFER_EXIT_RESP, 0xDEU, 0xADU, 0xBEU, 0xEFU, 0U, 0U, 0U};
    uint32_t echoedCrc = 0U;
    uint32_t len;

    len = buildRequest(&withCrc, buf, sizeof(buf));
    printBytes("RequestTransferExit (with CRC)", buf, len);

    if (parseResponse(resp, 5U, &echoedCrc) != 0U) {
        printf("Response SID: 0x%02X, echoed CRC: 0x%08lX\n",
               resp[0], (unsigned long)echoedCrc);
    }

    len = buildRequest(&noCrc, buf, sizeof(buf));
    printBytes("RequestTransferExit (no param)", buf, len);

    return 0;
}
