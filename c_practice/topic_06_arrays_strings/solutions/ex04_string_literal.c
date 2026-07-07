/**
 * Topic 06 - Exercise 04: String literal vs char array
 * STM32 context: const status strings in flash vs mutable TX buffer
 * Build: gcc ex04_string_literal.c -o ex04 && ./ex04
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *status_flash = "READY";          /* points to read-only literal */
    char tx_buf[] = "READY";                     /* mutable copy on stack */

    printf("status_flash: %s (const pointer)\n", status_flash);
    printf("tx_buf before: %s\n", tx_buf);

    tx_buf[0] = 'B';  /* OK: local array is writable */
    printf("tx_buf after:  %s\n", tx_buf);

    /* Modifying string literal is undefined behavior — do NOT do this on MCU:
     * ((char *)status_flash)[0] = 'X';
     */
    printf("Literal stored in .rodata; tx_buf size=%zu includes NUL\n",
           sizeof(tx_buf));
    return 0;
}
