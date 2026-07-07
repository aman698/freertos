/*
 * ex10_pool_allocator.c - Fixed-size block allocation without heap.
 * Key concept: memory pools give deterministic allocation.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BLOCK_COUNT 3U
#define BLOCK_SIZE  8U

static uint8_t pool[BLOCK_COUNT][BLOCK_SIZE];
static bool used[BLOCK_COUNT];

static void *pool_alloc(void)
{
    for (size_t i = 0U; i < BLOCK_COUNT; i++) {
        if (!used[i]) {
            used[i] = true;
            return pool[i];
        }
    }
    return NULL;
}

static void pool_free(void *ptr)
{
    for (size_t i = 0U; i < BLOCK_COUNT; i++) {
        if (ptr == pool[i]) {
            used[i] = false;
        }
    }
}

int main(void)
{
    void *a = pool_alloc();
    void *b = pool_alloc();
    printf("a=%s b=%s\n", a != NULL ? "ok" : "fail", b != NULL ? "ok" : "fail");
    pool_free(a);
    printf("after free, c=%s\n", pool_alloc() != NULL ? "ok" : "fail");
    return 0;
}
