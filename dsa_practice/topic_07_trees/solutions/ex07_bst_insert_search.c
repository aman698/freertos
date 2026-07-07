/* Insert and search in a BST using a static node pool. */
#include <stdbool.h>
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;
static Node pool[8];
static int used;

static Node *insert(Node *root, int v)
{
    if (root == NULL) {
        pool[used] = (Node){v, NULL, NULL};
        return &pool[used++];
    }
    if (v < root->v) root->l = insert(root->l, v);
    else if (v > root->v) root->r = insert(root->r, v);
    return root;
}

static bool search(Node *root, int v)
{
    if (root == NULL) return false;
    if (root->v == v) return true;
    return search(v < root->v ? root->l : root->r, v);
}

int main(void)
{
    Node *root = NULL;
    root = insert(root, 5); insert(root, 2); insert(root, 8);
    printf("found=%s\n", search(root, 8) ? "yes" : "no");
    return 0;
}
