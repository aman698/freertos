/* Find first repeating small integer. */
#include <stdio.h>

int main(void)
{
    int a[] = {4, 2, 3, 2, 4};
    int seen[10] = {0};
    int repeat = -1;
    for (int i = 0; i < 5; i++) {
        if (seen[a[i]]) { repeat = a[i]; break; }
        seen[a[i]] = 1;
    }
    printf("first_repeat=%d\n", repeat);
    return 0;
}
