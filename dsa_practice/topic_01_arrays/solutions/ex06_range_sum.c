/* Answer range sum query [l, r] using prefix sums. */
#include <stdio.h>

int main(void)
{
    int a[] = {3, 1, 4, 1, 5};
    int prefix[6] = {0};
    for (size_t i = 0; i < 5; i++) prefix[i + 1] = prefix[i] + a[i];
    size_t l = 1, r = 3;
    printf("sum[%zu,%zu]=%d\n", l, r, prefix[r + 1] - prefix[l]);
    return 0;
}
