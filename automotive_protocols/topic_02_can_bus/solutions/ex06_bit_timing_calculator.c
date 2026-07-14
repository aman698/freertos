/*
 * ex06_bit_timing_calculator.c - Derive CAN bit-timing register fields from clock and bit rate.
 * Key concept: bit time = Sync Seg + Prop Seg + Phase Seg1 + Phase Seg2, split across BRP/TSEG1/TSEG2/SJW.
 */
#include <stdint.h>
#include <stdio.h>

#define CAN_TOTAL_TQ   10U /* Sync(1) + TSEG1 + TSEG2, chosen for a clean example */
#define CAN_MAX_SJW    4U

typedef struct {
    uint16_t brp;
    uint8_t  tseg1;
    uint8_t  tseg2;
    uint8_t  sjw;
    uint32_t actualBitRate;
    uint8_t  samplePointPct;
} can_bit_timing_t;

static can_bit_timing_t can_calc_bit_timing(uint32_t canClkHz, uint32_t bitRateHz, uint8_t samplePointPct)
{
    can_bit_timing_t bt = {0};

    uint32_t tqFreq = bitRateHz * CAN_TOTAL_TQ;
    bt.brp = (uint16_t)(canClkHz / tqFreq); /* time quanta clock divider */
    if (bt.brp == 0U) {
        bt.brp = 1U;
    }

    /* Sync Seg = 1 Tq always; remaining (CAN_TOTAL_TQ - 1) split by sample point */
    uint8_t segAfterSync = (uint8_t)(CAN_TOTAL_TQ - 1U);
    uint8_t tseg1 = (uint8_t)(((uint32_t)samplePointPct * CAN_TOTAL_TQ) / 100U);
    if (tseg1 == 0U) {
        tseg1 = 1U;
    }
    if (tseg1 > segAfterSync) {
        tseg1 = segAfterSync;
    }
    bt.tseg1 = (uint8_t)(tseg1 - 1U + 1U); /* Prop Seg + Phase Seg1 combined */
    bt.tseg2 = (uint8_t)(segAfterSync - bt.tseg1);
    if (bt.tseg2 == 0U) {
        bt.tseg2 = 1U;
        bt.tseg1 = (uint8_t)(segAfterSync - bt.tseg2);
    }

    bt.sjw = (bt.tseg2 < CAN_MAX_SJW) ? bt.tseg2 : CAN_MAX_SJW;
    bt.actualBitRate = canClkHz / ((uint32_t)bt.brp * CAN_TOTAL_TQ);
    bt.samplePointPct = (uint8_t)(((uint32_t)(1U + bt.tseg1) * 100U) / CAN_TOTAL_TQ);

    return bt;
}

int main(void)
{
    uint32_t canClkHz     = 36000000U; /* 36 MHz APB clock, bxCAN-style example */
    uint32_t bitRateHz    = 500000U;   /* 500 kbit/s target */
    uint8_t  samplePctReq = 75U;       /* desired ~75% sample point */

    can_bit_timing_t bt = can_calc_bit_timing(canClkHz, bitRateHz, samplePctReq);

    printf("CAN clock       = %lu Hz\n", (unsigned long)canClkHz);
    printf("Requested rate  = %lu bit/s, sample point ~%u%%\n",
           (unsigned long)bitRateHz, samplePctReq);
    printf("BRP             = %u\n", bt.brp);
    printf("TSEG1 (Prop+PS1)= %u Tq\n", bt.tseg1);
    printf("TSEG2 (PS2)     = %u Tq\n", bt.tseg2);
    printf("SJW             = %u Tq\n", bt.sjw);
    printf("Actual bit rate = %lu bit/s\n", (unsigned long)bt.actualBitRate);
    printf("Actual sample   = %u%%\n", bt.samplePointPct);

    return 0;
}
