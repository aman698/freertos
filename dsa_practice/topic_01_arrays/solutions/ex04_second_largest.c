/* Find second largest distinct value. */
#include <limits.h>
#include <stdio.h>

int main(void)
{
    int a[] = {5, 8, 1, 8, 3, 7};
    int first = INT_MIN, second = INT_MIN;
    for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        if (a[i] > first) {
            second = first;
            first = a[i];
        } else if (a[i] < first && a[i] > second) {
            second = a[i];
        }
    }
    printf("second=%d\n", second);
    return 0;
}
