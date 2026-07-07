/* Hash chaining with static linked nodes. */
#include <stdio.h>

#define BUCKETS 3

typedef struct Node { int key; struct Node *next; } Node;

int main(void)
{
    Node nodes[3] = {{3, NULL}, {6, NULL}, {4, NULL}};
    Node *bucket[BUCKETS] = {0};
    for (int i = 0; i < 3; i++) {
        int h = nodes[i].key % BUCKETS;
        nodes[i].next = bucket[h];
        bucket[h] = &nodes[i];
    }
    for (int b = 0; b < BUCKETS; b++) {
        printf("%d:", b);
        for (Node *p = bucket[b]; p != NULL; p = p->next) printf(" %d", p->key);
        putchar('\n');
    }
    return 0;
}
