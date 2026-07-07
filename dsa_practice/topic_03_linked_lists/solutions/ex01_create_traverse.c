/* Create and traverse a static singly linked list. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

int main(void)
{
    Node c = {3, NULL}, b = {2, &c}, a = {1, &b};
    for (Node *p = &a; p != NULL; p = p->next) printf("%d ", p->data);
    putchar('\n');
    return 0;
}
