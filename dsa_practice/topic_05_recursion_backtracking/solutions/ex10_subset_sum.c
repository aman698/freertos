/* Check if any subset sums to target. */
#include <stdbool.h>
#include <stdio.h>

static bool subset_sum(const int a[], int n, int i, int target)
{
    if (target == 0) return true;
    if (i == n) return false;
    return subset_sum(a, n, i + 1, target) || subset_sum(a, n, i + 1, target - a[i]);
}

int main(void)
{
    int a[] = {3, 4, 7};
    printf("exists=%s\n", subset_sum(a, 3, 0, 10) ? "yes" : "no");
    return 0;
}
