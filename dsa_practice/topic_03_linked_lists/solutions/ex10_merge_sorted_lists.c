/* Merge two sorted linked lists using existing nodes. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

static Node *merge(Node *a, Node *b)
{
    Node dummy = {0, NULL};
    Node *tail = &dummy;
    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a != NULL) ? a : b;
    return dummy.next;
}

int main(void)
{
    Node a2 = {3, NULL}, a1 = {1, &a2};
    Node b2 = {4, NULL}, b1 = {2, &b2};
    Node *head = merge(&a1, &b1);
    for (Node *p = head; p != NULL; p = p->next) printf("%d ", p->data);
    putchar('\n');
    return 0;
}
