/*
 * ex12_bxcan_filter_bank.c - Simulate STM32 bxCAN filter banks in mask mode and list mode.
 * Key concept: mask mode accepts (id & mask) == (filterId & mask); list mode accepts exact ID matches only.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FILTER_LIST_SIZE 2U

typedef enum {
    CAN_FILTER_MODE_MASK = 0,
    CAN_FILTER_MODE_LIST
} can_filter_mode_t;

typedef struct {
    can_filter_mode_t mode;
    uint16_t          filterId;
    uint16_t          maskId;                    /* used in mask mode */
    uint16_t          listIds[FILTER_LIST_SIZE];  /* used in list mode */
} can_filter_bank_t;

static uint8_t can_filter_match(const can_filter_bank_t *bank, uint16_t rxId)
{
    if (bank == NULL) {
        return 0U;
    }
    if (bank->mode == CAN_FILTER_MODE_MASK) {
        return ((rxId & bank->maskId) == (bank->filterId & bank->maskId)) ? 1U : 0U;
    }
    for (uint8_t i = 0U; i < FILTER_LIST_SIZE; i++) {
        if (rxId == bank->listIds[i]) {
            return 1U;
        }
    }
    return 0U;
}

int main(void)
{
    can_filter_bank_t maskBank = {
        .mode     = CAN_FILTER_MODE_MASK,
        .filterId = 0x100U,
        .maskId   = 0x7F0U /* accept 0x100-0x10F */
    };

    can_filter_bank_t listBank = {
        .mode     = CAN_FILTER_MODE_LIST,
        .listIds  = { 0x200U, 0x2AAU }
    };

    uint16_t testIds[] = { 0x100U, 0x10FU, 0x110U, 0x200U, 0x2AAU, 0x2ABU };
    size_t testCount = sizeof(testIds) / sizeof(testIds[0]);

    printf("Mask-mode bank: filterId=0x%03X maskId=0x%03X\n", maskBank.filterId, maskBank.maskId);
    for (size_t i = 0U; i < testCount; i++) {
        uint8_t matched = can_filter_match(&maskBank, testIds[i]);
        printf("  ID=0x%03X -> %s\n", testIds[i], matched ? "ACCEPT" : "reject");
    }

    printf("\nList-mode bank: accepts {0x%03X, 0x%03X}\n", listBank.listIds[0], listBank.listIds[1]);
    for (size_t i = 0U; i < testCount; i++) {
        uint8_t matched = can_filter_match(&listBank, testIds[i]);
        printf("  ID=0x%03X -> %s\n", testIds[i], matched ? "ACCEPT" : "reject");
    }

    return 0;
}
