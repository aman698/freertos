/* Two-sum using a simple seen table for small values. */
#include <stdio.h>

int main(void)
{
    int a[] = {2, 7, 11, 15};
    int seen[32] = {0};
    int target = 9;
    for (int i = 0; i < 4; i++) {
        int need = target - a[i];
        if (need >= 0 && need < 32 && seen[need]) {
            printf("pair=%d,%d\n", need, a[i]);
            break;
        }
        seen[a[i]] = 1;
    }
    return 0;
}
