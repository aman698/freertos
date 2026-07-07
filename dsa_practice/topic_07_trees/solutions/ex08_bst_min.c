/* Find minimum value in a BST. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

int main(void)
{
    Node a = {1, NULL, NULL}, b = {3, NULL, NULL}, root = {2, &a, &b};
    Node *p = &root;
    while (p->l != NULL) p = p->l;
    printf("min=%d\n", p->v);
    return 0;
}
