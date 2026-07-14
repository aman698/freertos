/*
 * ex09_dtc_encode_decode.c - Pack/unpack a 3-byte DTC plus its status byte.
 * Key concept: DTC status bits report test/pending/confirmed fault history.
 */
#include <stdint.h>
#include <stdio.h>

#define STATUS_TEST_FAILED               0x01U
#define STATUS_TEST_FAILED_THIS_CYCLE    0x02U
#define STATUS_PENDING_DTC               0x04U
#define STATUS_CONFIRMED_DTC             0x08U
#define STATUS_CONFIRMED_SINCE_CLEAR     0x40U
#define STATUS_WARNING_INDICATOR         0x80U

typedef struct {
    uint8_t high;
    uint8_t mid;
    uint8_t low;
    uint8_t status;
} Dtc_t;

static uint32_t pack_dtc(const Dtc_t *dtc)
{
    if (dtc == NULL) {
        return 0U;
    }
    return ((uint32_t)dtc->high << 24) | ((uint32_t)dtc->mid << 16) |
           ((uint32_t)dtc->low << 8) | (uint32_t)dtc->status;
}

static void unpack_dtc(uint32_t packed, Dtc_t *dtc)
{
    if (dtc == NULL) {
        return;
    }
    dtc->high   = (uint8_t)((packed >> 24) & 0xFFU);
    dtc->mid    = (uint8_t)((packed >> 16) & 0xFFU);
    dtc->low    = (uint8_t)((packed >> 8) & 0xFFU);
    dtc->status = (uint8_t)(packed & 0xFFU);
}

static void print_status_flags(uint8_t status)
{
    printf("Status flags:\n");
    printf("  testFailed              : %s\n", (status & STATUS_TEST_FAILED) ? "1" : "0");
    printf("  testFailedThisCycle     : %s\n", (status & STATUS_TEST_FAILED_THIS_CYCLE) ? "1" : "0");
    printf("  pendingDTC              : %s\n", (status & STATUS_PENDING_DTC) ? "1" : "0");
    printf("  confirmedDTC            : %s\n", (status & STATUS_CONFIRMED_DTC) ? "1" : "0");
    printf("  confirmedSinceLastClear : %s\n", (status & STATUS_CONFIRMED_SINCE_CLEAR) ? "1" : "0");
    printf("  warningIndicatorRequest : %s\n", (status & STATUS_WARNING_INDICATOR) ? "1" : "0");
}

int main(void)
{
    Dtc_t original = {0x01U, 0x23U, 0x45U,
                       STATUS_TEST_FAILED | STATUS_CONFIRMED_DTC | STATUS_WARNING_INDICATOR};

    uint32_t packed = pack_dtc(&original);
    printf("Packed DTC: 0x%08X\n", (unsigned int)packed);

    Dtc_t unpacked;
    unpack_dtc(packed, &unpacked);

    printf("DTC bytes : 0x%02X 0x%02X 0x%02X  status=0x%02X\n",
           unpacked.high, unpacked.mid, unpacked.low, unpacked.status);

    print_status_flags(unpacked.status);

    return 0;
}
