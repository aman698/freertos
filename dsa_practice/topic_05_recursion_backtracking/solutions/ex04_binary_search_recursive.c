/* Recursive binary search in sorted array. */
#include <stdio.h>

static int search(const int a[], int l, int r, int target)
{
    if (l > r) return -1;
    int m = l + (r - l) / 2;
    if (a[m] == target) return m;
    return (target < a[m]) ? search(a, l, m - 1, target) : search(a, m + 1, r, target);
}

int main(void)
{
    int a[] = {1, 3, 5, 7};
    printf("index=%d\n", search(a, 0, 3, 5));
    return 0;
}
