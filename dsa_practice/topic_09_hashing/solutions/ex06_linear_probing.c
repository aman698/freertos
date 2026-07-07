/* Open-addressing hash table with linear probing. */
#include <stdio.h>

#define CAP 7
#define EMPTY -1

int main(void)
{
    int table[CAP];
    int keys[] = {10, 17, 24};
    for (int i = 0; i < CAP; i++) table[i] = EMPTY;
    for (int k = 0; k < 3; k++) {
        int idx = keys[k] % CAP;
        while (table[idx] != EMPTY) idx = (idx + 1) % CAP;
        table[idx] = keys[k];
    }
    for (int i = 0; i < CAP; i++) printf("%d ", table[i]);
    putchar('\n');
    return 0;
}
