/*
 * ex01_request_download.c - Build and parse a UDS RequestDownload (0x34) message.
 * Key concept: addressAndLengthFormatIdentifier controls address/size byte widths.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_REQUEST_DOWNLOAD       0x34U
#define SID_REQUEST_DOWNLOAD_RESP  0x74U
#define MAX_MSG_LEN                16U

typedef struct {
    uint8_t  dataFormatIdentifier;      /* high nibble compression, low nibble encryption */
    uint8_t  addressAndLengthFormatId;  /* high nibble = size bytes, low nibble = address bytes */
    uint32_t memoryAddress;
    uint32_t memorySize;
} RequestDownloadReq_t;

typedef struct {
    uint8_t  lengthFormatId;   /* high nibble = byte width of maxNumberOfBlockLength */
    uint32_t maxNumberOfBlockLength;
} RequestDownloadResp_t;

static uint32_t buildRequest(const RequestDownloadReq_t *req, uint8_t *out, uint32_t outCap)
{
    uint8_t addrBytes;
    uint8_t sizeBytes;
    uint32_t idx = 0U;

    if ((req == NULL) || (out == NULL)) {
        return 0U;
    }

    addrBytes = (uint8_t)(req->addressAndLengthFormatId & 0x0FU);
    sizeBytes = (uint8_t)((req->addressAndLengthFormatId >> 4) & 0x0FU);

    if (outCap < (uint32_t)(3U + addrBytes + sizeBytes)) {
        return 0U;
    }

    out[idx] = SID_REQUEST_DOWNLOAD;
    idx++;
    out[idx] = req->dataFormatIdentifier;
    idx++;
    out[idx] = req->addressAndLengthFormatId;
    idx++;

    for (uint8_t i = 0U; i < addrBytes; i++) {
        uint32_t shift = (uint32_t)(addrBytes - 1U - i) * 8U;
        out[idx] = (uint8_t)((req->memoryAddress >> shift) & 0xFFU);
        idx++;
    }
    for (uint8_t i = 0U; i < sizeBytes; i++) {
        uint32_t shift = (uint32_t)(sizeBytes - 1U - i) * 8U;
        out[idx] = (uint8_t)((req->memorySize >> shift) & 0xFFU);
        idx++;
    }

    return idx;
}

static uint8_t parseRequest(const uint8_t *bytes, uint32_t len, RequestDownloadReq_t *reqOut)
{
    uint8_t addrBytes;
    uint8_t sizeBytes;
    uint32_t idx = 3U;

    if ((bytes == NULL) || (reqOut == NULL) || (len < 3U)) {
        return 0U;
    }
    if (bytes[0] != SID_REQUEST_DOWNLOAD) {
        return 0U;
    }

    reqOut->dataFormatIdentifier = bytes[1];
    reqOut->addressAndLengthFormatId = bytes[2];
    addrBytes = (uint8_t)(bytes[2] & 0x0FU);
    sizeBytes = (uint8_t)((bytes[2] >> 4) & 0x0FU);

    if (len < (uint32_t)(3U + addrBytes + sizeBytes)) {
        return 0U;
    }

    reqOut->memoryAddress = 0U;
    for (uint8_t i = 0U; i < addrBytes; i++) {
        reqOut->memoryAddress = (reqOut->memoryAddress << 8) | bytes[idx];
        idx++;
    }

    reqOut->memorySize = 0U;
    for (uint8_t i = 0U; i < sizeBytes; i++) {
        reqOut->memorySize = (reqOut->memorySize << 8) | bytes[idx];
        idx++;
    }

    return 1U;
}

static uint32_t buildResponse(const RequestDownloadResp_t *resp, uint8_t *out, uint32_t outCap)
{
    uint8_t lenBytes;
    uint32_t idx = 0U;

    if ((resp == NULL) || (out == NULL)) {
        return 0U;
    }

    lenBytes = (uint8_t)((resp->lengthFormatId >> 4) & 0x0FU);

    if (outCap < (uint32_t)(2U + lenBytes)) {
        return 0U;
    }

    out[idx] = SID_REQUEST_DOWNLOAD_RESP;
    idx++;
    out[idx] = resp->lengthFormatId;
    idx++;

    for (uint8_t i = 0U; i < lenBytes; i++) {
        uint32_t shift = (uint32_t)(lenBytes - 1U - i) * 8U;
        out[idx] = (uint8_t)((resp->maxNumberOfBlockLength >> shift) & 0xFFU);
        idx++;
    }

    return idx;
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
    uint8_t buf[MAX_MSG_LEN];
    RequestDownloadReq_t req = {0x00U, 0x44U, 0x08004000U, 0x00010000U};
    RequestDownloadReq_t parsed;
    RequestDownloadResp_t resp = {0x20U, 0x0400U};
    uint32_t reqLen;
    uint32_t respLen;

    reqLen = buildRequest(&req, buf, sizeof(buf));
    printBytes("RequestDownload", buf, reqLen);

    if (parseRequest(buf, reqLen, &parsed) != 0U) {
        printf("Parsed: dataFormatId=0x%02X addr=0x%08lX size=0x%08lX\n",
               parsed.dataFormatIdentifier,
               (unsigned long)parsed.memoryAddress,
               (unsigned long)parsed.memorySize);
    }

    respLen = buildResponse(&resp, buf, sizeof(buf));
    printBytes("RequestDownload response", buf, respLen);
    printf("maxNumberOfBlockLength = 0x%04lX\n", (unsigned long)resp.maxNumberOfBlockLength);

    return 0;
}
