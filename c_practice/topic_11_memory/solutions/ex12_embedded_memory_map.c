/*
 * ex12_embedded_memory_map.c - Simulate common firmware memory regions.
 * Key concept: embedded code must know where data lives.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    const char *name;
    uintptr_t start;
    uint32_t size;
} Region_t;

int main(void)
{
    const Region_t map[] = {
        {"FLASH", 0x08000000UL, 512UL * 1024UL},
        {"SRAM",  0x20000000UL, 128UL * 1024UL},
        {"PERIPH",0x40000000UL, 512UL * 1024UL}
    };

    for (size_t i = 0U; i < sizeof(map) / sizeof(map[0]); i++) {
        printf("%s start=0x%08lX size=%lu bytes\n",
               map[i].name, (unsigned long)map[i].start, (unsigned long)map[i].size);
    }
    return 0;
}
