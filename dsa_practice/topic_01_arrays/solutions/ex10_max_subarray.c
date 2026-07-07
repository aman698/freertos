/* Kadane algorithm for maximum subarray sum. */
#include <stdio.h>

int main(void)
{
    int a[] = {-2, 1, -3, 4, -1, 2, 1, -5};
    int best = a[0], cur = a[0];
    for (size_t i = 1; i < sizeof(a) / sizeof(a[0]); i++) {
        cur = (cur + a[i] > a[i]) ? cur + a[i] : a[i];
        if (cur > best) best = cur;
    }
    printf("max_subarray=%d\n", best);
    return 0;
}
