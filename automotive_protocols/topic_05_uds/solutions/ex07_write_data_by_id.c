/*
 * ex07_write_data_by_id.c - Simulate WriteDataByIdentifier (0x2E) with write-protected DIDs.
 * Key concept: unknown DIDs and read-only DIDs must be rejected with an NRC.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_WRITE_DATA_BY_IDENTIFIER 0x2EU
#define NRC_CONDITIONS_NOT_CORRECT 0x22U
#define NRC_REQUEST_OUT_OF_RANGE 0x31U

typedef struct {
    uint16_t did;
    const char *name;
    uint8_t writable;
} WriteDidEntry_t;

static const WriteDidEntry_t DID_TABLE[] = {
    {0xF190U, "VIN",          0U},
    {0xF195U, "SW_VERSION",   0U},
    {0x0102U, "USER_CONFIG",  1U}
};

static const size_t DID_TABLE_LEN = sizeof(DID_TABLE) / sizeof(DID_TABLE[0]);

static const WriteDidEntry_t *find_did(uint16_t did)
{
    for (size_t i = 0U; i < DID_TABLE_LEN; i++) {
        if (DID_TABLE[i].did == did) {
            return &DID_TABLE[i];
        }
    }
    return NULL;
}

static void handle_write_by_id(uint16_t did, uint8_t data)
{
    const WriteDidEntry_t *entry = find_did(did);

    printf("Request : 0x%02X 0x%02X 0x%02X data=0x%02X\n",
           SID_WRITE_DATA_BY_IDENTIFIER, (uint8_t)(did >> 8), (uint8_t)(did & 0xFFU), data);

    if (entry == NULL) {
        printf("Response: 0x7F 0x%02X 0x%02X (requestOutOfRange - unknown DID)\n",
               SID_WRITE_DATA_BY_IDENTIFIER, NRC_REQUEST_OUT_OF_RANGE);
        return;
    }

    if (entry->writable == 0U) {
        printf("Response: 0x7F 0x%02X 0x%02X (conditionsNotCorrect - %s is read-only)\n",
               SID_WRITE_DATA_BY_IDENTIFIER, NRC_CONDITIONS_NOT_CORRECT, entry->name);
        return;
    }

    printf("Response: 0x%02X 0x%02X 0x%02X (%s updated)\n",
           SID_WRITE_DATA_BY_IDENTIFIER + 0x40U,
           (uint8_t)(did >> 8), (uint8_t)(did & 0xFFU), entry->name);
}

int main(void)
{
    handle_write_by_id(0x0102U, 0x07U);
    handle_write_by_id(0xF190U, 0x01U);
    handle_write_by_id(0x9999U, 0x01U);

    return 0;
}
