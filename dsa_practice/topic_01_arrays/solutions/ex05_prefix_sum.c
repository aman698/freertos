/* Build prefix sums where prefix[i+1] is sum of a[0..i]. */
#include <stdio.h>

int main(void)
{
    int a[] = {3, 1, 4, 1, 5};
    int prefix[6] = {0};
    for (size_t i = 0; i < 5; i++) {
        prefix[i + 1] = prefix[i] + a[i];
    }
    for (size_t i = 0; i < 6; i++) printf("%d ", prefix[i]);
    putchar('\n');
    return 0;
}
