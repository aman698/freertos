/* Hash integers into buckets with modulo. */
#include <stdio.h>

#define BUCKETS 5

int main(void)
{
    int keys[] = {10, 21, 32};
    for (int i = 0; i < 3; i++) {
        printf("key %d -> bucket %d\n", keys[i], keys[i] % BUCKETS);
    }
    return 0;
}
