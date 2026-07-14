/*
 * ex02_extended_id_pack.c - Pack/unpack a CAN 2.0B 29-bit extended identifier.
 * Key concept: the 29-bit ID is an 11-bit base identifier followed by an 18-bit ID extension.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define CAN_BASE_ID_MASK 0x7FFU      /* 11 bits */
#define CAN_EXT_ID_MASK  0x3FFFFU    /* 18 bits */
#define CAN_EXT_ID_BITS  18U
#define CAN_29BIT_MASK   0x1FFFFFFFU /* 29 bits */

static uint32_t can_pack_extended_id(uint16_t baseId, uint32_t extId)
{
    uint32_t id29 = ((uint32_t)(baseId & CAN_BASE_ID_MASK) << CAN_EXT_ID_BITS) |
                    (extId & CAN_EXT_ID_MASK);
    return id29 & CAN_29BIT_MASK;
}

static void can_unpack_extended_id(uint32_t id29, uint16_t *baseId, uint32_t *extId)
{
    if ((baseId == NULL) || (extId == NULL)) {
        return;
    }
    *baseId = (uint16_t)((id29 >> CAN_EXT_ID_BITS) & CAN_BASE_ID_MASK);
    *extId  = id29 & CAN_EXT_ID_MASK;
}

int main(void)
{
    uint16_t base = 0x123U;
    uint32_t ext  = 0x2ABCDU;

    uint32_t packed = can_pack_extended_id(base, ext);
    printf("Base ID = 0x%03X, Extension = 0x%05lX\n", base, (unsigned long)ext);
    printf("Packed 29-bit ID = 0x%08lX\n", (unsigned long)packed);

    uint16_t baseOut = 0U;
    uint32_t extOut  = 0U;
    can_unpack_extended_id(packed, &baseOut, &extOut);

    printf("Unpacked Base ID = 0x%03X, Extension = 0x%05lX\n", baseOut, (unsigned long)extOut);
    printf("Round-trip match: %s\n", ((baseOut == base) && (extOut == ext)) ? "YES" : "NO");
    return 0;
}
