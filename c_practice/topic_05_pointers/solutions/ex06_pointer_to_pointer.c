/*
 * ex06_pointer_to_pointer.c — Double pointer for out-parameters
 * Key concept: function can modify caller's pointer via T**.
 */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

static void allocate_buffer(uint8_t **buf_out, size_t *len_out)
{
    static uint8_t pool[16];
    if (buf_out != NULL) {
        *buf_out = pool;
    }
    if (len_out != NULL) {
        *len_out = sizeof(pool);
    }
}

int main(void)
{
    uint8_t *buf = NULL;
    size_t len = 0U;

    allocate_buffer(&buf, &len);
    if (buf != NULL) {
        buf[0] = 0x42U;
        printf("Buffer at %p, len=%zu, buf[0]=0x%02X\n",
               (void *)buf, len, buf[0]);
    }

    return 0;
}
