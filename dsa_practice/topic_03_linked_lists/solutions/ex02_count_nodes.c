/* Count nodes in a linked list. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

int main(void)
{
    Node c = {30, NULL}, b = {20, &c}, a = {10, &b};
    int count = 0;
    for (Node *p = &a; p != NULL; p = p->next) count++;
    printf("count=%d\n", count);
    return 0;
}
