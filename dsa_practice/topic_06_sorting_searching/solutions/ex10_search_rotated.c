/* Search target in rotated sorted array. */
#include <stdio.h>

int main(void)
{
    int a[] = {4, 5, 6, 1, 2, 3};
    int l = 0, r = 5, target = 2, ans = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == target) { ans = m; break; }
        if (a[l] <= a[m]) {
            if (a[l] <= target && target < a[m]) r = m - 1; else l = m + 1;
        } else {
            if (a[m] < target && target <= a[r]) l = m + 1; else r = m - 1;
        }
    }
    printf("index=%d\n", ans);
    return 0;
}
