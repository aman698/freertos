/*
 * ex09_memory_set.c - Clear a structure before filling it.
 * Key concept: memset is common for zero initialization of POD data.
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint8_t id;
    uint16_t value;
    uint8_t flags;
} Packet_t;

int main(void)
{
    Packet_t pkt;
    memset(&pkt, 0, sizeof(pkt));
    pkt.id = 7U;
    printf("id=%u value=%u flags=%u\n", pkt.id, pkt.value, pkt.flags);
    return 0;
}
