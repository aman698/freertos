/*
 * ex09_array_size_macro.c — ARRAY_SIZE for element count
 * Key concept: sizeof array / sizeof element — never use on pointers!
 */
#include <stdint.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(void)
{
    uint16_t samples[] = { 100, 200, 300, 400, 500 };
    printf("Array has %zu elements\n", ARRAY_SIZE(samples));
    return 0;
}
