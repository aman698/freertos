/* Sum array elements. Time O(n), space O(1). */
#include <stdio.h>

int main(void)
{
    int a[] = {2, 4, 6, 8};
    int sum = 0;
    for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        sum += a[i];
    }
    printf("sum=%d\n", sum);
    return 0;
}
