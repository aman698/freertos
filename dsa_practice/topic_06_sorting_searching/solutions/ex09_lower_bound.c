/* Lower bound: first index with value >= target. */
#include <stdio.h>

int main(void)
{
    int a[] = {1, 3, 3, 5};
    int l = 0, r = 4, target = 3;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] < target) l = m + 1; else r = m;
    }
    printf("lower_bound=%d\n", l);
    return 0;
}
