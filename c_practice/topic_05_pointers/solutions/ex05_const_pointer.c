/*
 * ex05_const_pointer.c — const data vs const pointer
 * Key concept: const T* = read-only data; T* const = fixed address.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t mmio_reg = 0U;

    const uint32_t flash_lut[] = { 100U, 200U, 300U };
    const uint32_t *read_only = flash_lut;   /* cannot modify *read_only */
    uint32_t *const fixed_addr = &mmio_reg;  /* cannot change fixed_addr */

    printf("LUT[1] = %lu (read-only table in flash)\n",
           (unsigned long)read_only[1]);

    *fixed_addr = 0x40021000UL;  /* OK — write through fixed pointer */
    printf("MMIO reg = 0x%08lX\n", (unsigned long)*fixed_addr);

    return 0;
}
