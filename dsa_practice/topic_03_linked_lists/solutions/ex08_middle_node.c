/* Find middle node using slow and fast pointers. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

int main(void)
{
    Node e = {5, NULL}, d = {4, &e}, c = {3, &d}, b = {2, &c}, a = {1, &b};
    Node *slow = &a, *fast = &a;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    printf("middle=%d\n", slow->data);
    return 0;
}
