/*
 * ex08_sort_comparator.c - qsort uses a comparator callback.
 * Key concept: standard library callback signature.
 */
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    int a = *(const int *)lhs;
    int b = *(const int *)rhs;
    return (a > b) - (a < b);
}

int main(void)
{
    int values[] = {9, 2, 5, 1};
    qsort(values, sizeof(values) / sizeof(values[0]), sizeof(values[0]), compare_ints);

    for (size_t i = 0U; i < sizeof(values) / sizeof(values[0]); i++) {
        printf("%d ", values[i]);
    }
    putchar('\n');
    return 0;
}
