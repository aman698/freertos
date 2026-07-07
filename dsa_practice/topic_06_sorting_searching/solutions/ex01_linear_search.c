/* Linear search in unsorted array. */
#include <stdio.h>

int main(void)
{
    int a[] = {4, 9, 1, 7};
    int target = 1, index = -1;
    for (int i = 0; i < 4; i++) if (a[i] == target) index = i;
    printf("index=%d\n", index);
    return 0;
}
