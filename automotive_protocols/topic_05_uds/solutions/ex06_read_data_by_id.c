/*
 * ex06_read_data_by_id.c - Simulate ReadDataByIdentifier (0x22) against a static DID table.
 * Key concept: positive response echoes the DID then appends its data bytes.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_READ_DATA_BY_IDENTIFIER 0x22U
#define NRC_REQUEST_OUT_OF_RANGE 0x31U

typedef struct {
    uint16_t did;
    const char *name;
    const char *value;
} DidEntry_t;

static const DidEntry_t DID_TABLE[] = {
    {0xF190U, "VIN",             "1HGCM82633A004352"},
    {0xF195U, "SW_VERSION",      "SWv2.4.1"},
    {0xF100U, "ENGINE_HOURS",    "01245"}
};

static const size_t DID_TABLE_LEN = sizeof(DID_TABLE) / sizeof(DID_TABLE[0]);

static const DidEntry_t *find_did(uint16_t did)
{
    for (size_t i = 0U; i < DID_TABLE_LEN; i++) {
        if (DID_TABLE[i].did == did) {
            return &DID_TABLE[i];
        }
    }
    return NULL;
}

static void handle_read_by_id(uint16_t did)
{
    const DidEntry_t *entry = find_did(did);

    printf("Request : 0x%02X 0x%02X 0x%02X\n",
           SID_READ_DATA_BY_IDENTIFIER, (uint8_t)(did >> 8), (uint8_t)(did & 0xFFU));

    if (entry == NULL) {
        printf("Response: 0x7F 0x%02X 0x%02X (requestOutOfRange - unknown DID)\n",
               SID_READ_DATA_BY_IDENTIFIER, NRC_REQUEST_OUT_OF_RANGE);
        return;
    }

    printf("Response: 0x%02X 0x%02X 0x%02X data=\"%s\" (%s)\n",
           SID_READ_DATA_BY_IDENTIFIER + 0x40U,
           (uint8_t)(did >> 8), (uint8_t)(did & 0xFFU),
           entry->value, entry->name);
}

int main(void)
{
    uint16_t requests[] = {0xF190U, 0xF195U, 0xF100U, 0xABCDU};
    size_t requests_len = sizeof(requests) / sizeof(requests[0]);

    for (size_t i = 0U; i < requests_len; i++) {
        handle_read_by_id(requests[i]);
    }

    return 0;
}
