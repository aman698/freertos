/*
 * ex09_address_claim.c - Resolve an address-claim conflict by NAME priority.
 * Key concept: on a tie, the lower 64-bit NAME wins and keeps the address.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define J1939_ADDR_CANNOT_CLAIM 254U

typedef struct {
    const char *label;
    uint64_t name;
    uint8_t address;
    bool arbitrary_addr_capable;
} ecu_node_t;

static void claim_defend(const ecu_node_t *winner, ecu_node_t *loser)
{
    if ((winner == NULL) || (loser == NULL)) {
        return;
    }

    printf("%s (NAME=0x%016llX) wins, keeps address 0x%02X\n",
           winner->label, (unsigned long long)winner->name, winner->address);

    if (loser->arbitrary_addr_capable) {
        loser->address = (uint8_t)(loser->address + 1U);
        printf("%s (NAME=0x%016llX) loses, moves to address 0x%02X\n",
               loser->label, (unsigned long long)loser->name, loser->address);
    } else {
        loser->address = (uint8_t)J1939_ADDR_CANNOT_CLAIM;
        printf("%s (NAME=0x%016llX) loses, not address-capable, address 0x%02X (cannot claim)\n",
               loser->label, (unsigned long long)loser->name, loser->address);
    }
}

static void resolve_conflict(ecu_node_t *a, ecu_node_t *b)
{
    if ((a == NULL) || (b == NULL)) {
        return;
    }

    if (a->address != b->address) {
        printf("No conflict: addresses differ\n");
        return;
    }

    if (a->name < b->name) {
        claim_defend(a, b);
    } else {
        claim_defend(b, a);
    }
}

int main(void)
{
    ecu_node_t engine_ecu = {"EngineECU", 0x1000000000000010ULL, 0x00U, false};
    ecu_node_t aftermarket_ecu = {"AftermarketECU", 0x2000000000000020ULL, 0x00U, true};

    printf("Both ECUs claim address 0x%02X\n", engine_ecu.address);
    resolve_conflict(&engine_ecu, &aftermarket_ecu);

    return 0;
}
