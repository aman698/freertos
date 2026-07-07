/*
 * ex07_singly_linked_list.c - Link static nodes.
 * Key concept: each node points to the next node.
 */
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node_t;

int main(void)
{
    Node_t n3 = {30, NULL};
    Node_t n2 = {20, &n3};
    Node_t n1 = {10, &n2};

    for (Node_t *cur = &n1; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->value);
    }
    return 0;
}
