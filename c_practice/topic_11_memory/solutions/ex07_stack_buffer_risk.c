/*
 * ex07_stack_buffer_risk.c - Keep task stack buffers small and bounded.
 * Key concept: large local arrays can overflow small embedded stacks.
 */
#include <stdint.h>
#include <stdio.h>

static void process_frame(void)
{
    uint8_t frame[32];
    for (size_t i = 0U; i < sizeof(frame); i++) {
        frame[i] = (uint8_t)i;
    }
    printf("frame bytes = %zu, last = %u\n", sizeof(frame), frame[31]);
}

int main(void)
{
    process_frame();
    puts("For larger buffers, consider static storage or a memory pool.");
    return 0;
}
