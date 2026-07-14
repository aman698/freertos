/*
 * ex08_name_field.c - Pack/unpack the 64-bit J1939 NAME field.
 * Key concept: NAME sub-fields are shifted/masked manually, not via C bitfields.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t identity_number;      /* bits 0-20  (21 bits) */
    uint16_t manufacturer_code;    /* bits 21-31 (11 bits) */
    uint8_t ecu_instance;          /* bits 32-34 (3 bits) */
    uint8_t function_instance;     /* bits 35-39 (5 bits) */
    uint8_t function;              /* bits 40-47 (8 bits) */
    uint8_t vehicle_system;        /* bits 49-55 (7 bits) */
    uint8_t vehicle_system_instance; /* bits 56-59 (4 bits) */
    uint8_t industry_group;        /* bits 60-62 (3 bits) */
    uint8_t arbitrary_addr_capable; /* bit 63 (1 bit) */
} j1939_name_t;

static uint64_t j1939_name_pack(const j1939_name_t *name)
{
    uint64_t out = 0ULL;

    if (name == NULL) {
        return 0ULL;
    }

    out |= ((uint64_t)name->identity_number & 0x1FFFFFULL);
    out |= ((uint64_t)name->manufacturer_code & 0x7FFULL) << 21;
    out |= ((uint64_t)name->ecu_instance & 0x7ULL) << 32;
    out |= ((uint64_t)name->function_instance & 0x1FULL) << 35;
    out |= ((uint64_t)name->function & 0xFFULL) << 40;
    out |= ((uint64_t)name->vehicle_system & 0x7FULL) << 49;
    out |= ((uint64_t)name->vehicle_system_instance & 0xFULL) << 56;
    out |= ((uint64_t)name->industry_group & 0x7ULL) << 60;
    out |= ((uint64_t)name->arbitrary_addr_capable & 0x1ULL) << 63;

    return out;
}

static void j1939_name_unpack(uint64_t raw, j1939_name_t *name)
{
    if (name == NULL) {
        return;
    }

    name->identity_number = (uint32_t)(raw & 0x1FFFFFULL);
    name->manufacturer_code = (uint16_t)((raw >> 21) & 0x7FFULL);
    name->ecu_instance = (uint8_t)((raw >> 32) & 0x7ULL);
    name->function_instance = (uint8_t)((raw >> 35) & 0x1FULL);
    name->function = (uint8_t)((raw >> 40) & 0xFFULL);
    name->vehicle_system = (uint8_t)((raw >> 49) & 0x7FULL);
    name->vehicle_system_instance = (uint8_t)((raw >> 56) & 0xFULL);
    name->industry_group = (uint8_t)((raw >> 60) & 0x7ULL);
    name->arbitrary_addr_capable = (uint8_t)((raw >> 63) & 0x1ULL);
}

int main(void)
{
    j1939_name_t original = {
        123456UL, /* identity_number */
        512U,     /* manufacturer_code */
        1U,       /* ecu_instance */
        0U,       /* function_instance */
        0U,       /* function: engine */
        1U,       /* vehicle_system */
        0U,       /* vehicle_system_instance */
        0U,       /* industry_group: on-highway */
        1U        /* arbitrary_addr_capable */
    };

    uint64_t raw = j1939_name_pack(&original);
    j1939_name_t decoded;

    j1939_name_unpack(raw, &decoded);

    printf("Packed NAME = 0x%016llX\n", (unsigned long long)raw);
    printf("identity_number:   %lu\n", (unsigned long)decoded.identity_number);
    printf("manufacturer_code: %u\n", decoded.manufacturer_code);
    printf("ecu_instance:      %u\n", decoded.ecu_instance);
    printf("function_instance: %u\n", decoded.function_instance);
    printf("function:          %u\n", decoded.function);
    printf("vehicle_system:    %u\n", decoded.vehicle_system);
    printf("vehicle_system_instance: %u\n", decoded.vehicle_system_instance);
    printf("industry_group:    %u\n", decoded.industry_group);
    printf("arbitrary_addr_capable: %u\n", decoded.arbitrary_addr_capable);

    return 0;
}
