/* Delete first node with matching value. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

static void delete_value(Node **head, int value)
{
    while (*head != NULL) {
        if ((*head)->data == value) {
            *head = (*head)->next;
            return;
        }
        head = &(*head)->next;
    }
}

int main(void)
{
    Node c = {3, NULL}, b = {2, &c}, a = {1, &b};
    Node *head = &a;
    delete_value(&head, 2);
    for (Node *p = head; p != NULL; p = p->next) printf("%d ", p->data);
    putchar('\n');
    return 0;
}
