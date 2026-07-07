/*
 * ex08_write_one_to_clear.c - Simulate write-one-to-clear flags.
 * Key concept: many status registers clear flags by writing 1 to those bits.
 */
#include <stdint.h>
#include <stdio.h>

#define RX_FLAG (1UL << 0U)
#define TX_FLAG (1UL << 1U)

static void clear_flags(uint32_t *status, uint32_t w1c_mask)
{
    *status &= ~w1c_mask;
}

int main(void)
{
    uint32_t status = RX_FLAG | TX_FLAG;
    clear_flags(&status, RX_FLAG);
    printf("status = 0x%08lX\n", (unsigned long)status);
    return 0;
}
