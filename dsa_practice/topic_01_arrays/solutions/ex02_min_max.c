/* Find minimum and maximum in one pass. */
#include <stdio.h>

int main(void)
{
    int a[] = {7, 2, 9, -1, 5};
    int min = a[0], max = a[0];
    for (size_t i = 1; i < sizeof(a) / sizeof(a[0]); i++) {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
    printf("min=%d max=%d\n", min, max);
    return 0;
}
