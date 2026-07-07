/* Detect a cycle using Floyd slow/fast pointers. */
#include <stdbool.h>
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

int main(void)
{
    Node c = {3, NULL}, b = {2, &c}, a = {1, &b};
    c.next = &b;
    Node *slow = &a, *fast = &a;
    bool cycle = false;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            cycle = true;
            break;
        }
    }
    printf("cycle=%s\n", cycle ? "yes" : "no");
    return 0;
}
