/*
 * ex09_array_pointer.c — Array decays to pointer to first element
 * Key concept: array name in expressions becomes pointer to element zero.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint16_t adc_buf[4] = { 1000, 1100, 1050, 1200 };
    uint16_t *p = adc_buf;  /* same as &adc_buf[0] */

    printf("adc_buf via pointer:\n");
    for (size_t i = 0U; i < 4U; i++) {
        printf("  [%zu] = %u (p+%zu)\n", i, *(p + i), i);
    }

    printf("adc_buf[i] equivalent to *(adc_buf + i)\n");
    return 0;
}
