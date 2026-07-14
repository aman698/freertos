/*
 * ex10_read_dtc_information.c - Simulate ReadDTCInformation (0x19) status-mask filtering.
 * Key concept: sub-function 0x02 reportDTCByStatusMask only returns matching DTCs.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_READ_DTC_INFORMATION 0x19U
#define SUB_REPORT_DTC_BY_STATUS_MASK 0x02U

#define STATUS_TEST_FAILED   0x01U
#define STATUS_PENDING_DTC   0x04U
#define STATUS_CONFIRMED_DTC 0x08U

typedef struct {
    uint8_t high;
    uint8_t mid;
    uint8_t low;
    uint8_t status;
} Dtc_t;

static const Dtc_t DTC_STORE[] = {
    {0x01U, 0x23U, 0x45U, STATUS_CONFIRMED_DTC | STATUS_TEST_FAILED},
    {0x02U, 0x10U, 0x0AU, STATUS_PENDING_DTC},
    {0x03U, 0x55U, 0x9CU, STATUS_CONFIRMED_DTC}
};

static const size_t DTC_STORE_LEN = sizeof(DTC_STORE) / sizeof(DTC_STORE[0]);

static void report_dtc_by_status_mask(uint8_t status_mask)
{
    printf("Request : 0x%02X 0x%02X mask=0x%02X\n",
           SID_READ_DTC_INFORMATION, SUB_REPORT_DTC_BY_STATUS_MASK, status_mask);
    printf("Response: 0x%02X 0x%02X availabilityMask=0xFF\n",
           SID_READ_DTC_INFORMATION + 0x40U, SUB_REPORT_DTC_BY_STATUS_MASK);

    size_t matches = 0U;
    for (size_t i = 0U; i < DTC_STORE_LEN; i++) {
        if ((DTC_STORE[i].status & status_mask) != 0U) {
            printf("  DTC 0x%02X%02X%02X status=0x%02X\n",
                   DTC_STORE[i].high, DTC_STORE[i].mid, DTC_STORE[i].low, DTC_STORE[i].status);
            matches++;
        }
    }

    if (matches == 0U) {
        printf("  (no DTCs match mask 0x%02X)\n", status_mask);
    }
}

int main(void)
{
    report_dtc_by_status_mask(STATUS_CONFIRMED_DTC);
    report_dtc_by_status_mask(STATUS_PENDING_DTC);
    report_dtc_by_status_mask(0x80U);

    return 0;
}
