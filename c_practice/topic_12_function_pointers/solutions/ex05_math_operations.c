/*
 * ex05_math_operations.c - Select behavior through a function pointer.
 * Key concept: strategy pattern in plain C.
 */
#include <stdio.h>

typedef int (*BinaryOp_t)(int a, int b);

static int add(int a, int b) { return a + b; }
static int mul(int a, int b) { return a * b; }

static void print_result(BinaryOp_t op, int a, int b)
{
    printf("result = %d\n", op(a, b));
}

int main(void)
{
    print_result(add, 3, 4);
    print_result(mul, 3, 4);
    return 0;
}
