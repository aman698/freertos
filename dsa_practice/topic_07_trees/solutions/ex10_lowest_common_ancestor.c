/* Lowest common ancestor in a BST. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

static Node *lca(Node *root, int a, int b)
{
    while (root != NULL) {
        if (a < root->v && b < root->v) root = root->l;
        else if (a > root->v && b > root->v) root = root->r;
        else return root;
    }
    return NULL;
}

int main(void)
{
    Node n1 = {1, NULL, NULL}, n3 = {3, NULL, NULL}, n2 = {2, &n1, &n3};
    Node n7 = {7, NULL, NULL}, root = {5, &n2, &n7};
    printf("lca=%d\n", lca(&root, 1, 3)->v);
    return 0;
}
