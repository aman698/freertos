/*
 * ex03_null_check.c — Always check NULL before dereference
 * Key concept: NULL pointer dereference is undefined — guard first.
 */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

static void write_register(volatile uint32_t *reg, uint32_t value)
{
    if (reg == NULL) {
        printf("ERROR: null register pointer — write skipped\n");
        return;
    }
    *reg = value;
    printf("Wrote 0x%08lX to register\n", (unsigned long)value);
}

int main(void)
{
    volatile uint32_t fake_cr = 0U;

    write_register(&fake_cr, 0x00000001UL);
    write_register(NULL, 0xDEADBEEFUL);

    return 0;
}
