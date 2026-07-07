/* Iterative binary search in sorted array. */
#include <stdio.h>

int main(void)
{
    int a[] = {1, 3, 5, 7, 9};
    int l = 0, r = 4, target = 7, ans = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == target) { ans = m; break; }
        if (target < a[m]) r = m - 1; else l = m + 1;
    }
    printf("index=%d\n", ans);
    return 0;
}
