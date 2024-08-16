#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};

void Traversallinkedlist(struct Node *ptr)
{
    while (ptr != NULL)
    {
        printf("Elements are:%d\n", ptr->data);
        ptr = ptr->next;
    }
}
// insert at first node
struct Node *insertatfirst(struct Node *head, int data)
{
    struct Node *ptr = (struct node *)malloc(sizeof(struct Node));

    ptr->next = head;
    ptr->data = data;
    return ptr;
}
// insert at index
struct Node *insertatindex(struct Node *head, int data, int index)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    if (ptr == NULL)
    {
        printf("Memory allocation failed\n");
        return head;
    }
    struct Node *p = head;

    int i = 0;
    while (i != index - 1 && p != NULL)

    {
        p = p->next;
        i++;
    }
    ptr->data = data;
    ptr->next = p->next;
    p->next = ptr;
    return head;
}

// insert at end of list
struct Node *insertatend(struct Node *head, int data)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr->data = data;
    struct Node *p = head;

    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = ptr;
    ptr->next = NULL;

    return head;
}
// insert elements after a node
struct Node *insertafternode(struct Node *head, struct Node *prevnode, int data)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr->data = data;
    ptr->next = prevnode->next;
    prevnode->next = ptr;

    return head;
}

int main()
{
    struct Node *head;
    struct Node *second;
    struct Node *third;

    head = (struct Node *)malloc(sizeof(struct Node));
    second = (struct Node *)malloc(sizeof(struct Node));
    third = (struct Node *)malloc(sizeof(struct Node));
    // link first and second node
    head->data = 7;
    head->next = second;
    // link second and third
    second->data = 11;
    second->next = third;
    // terminate the list at third node
    third->data = 22;
    third->next = NULL;

    Traversallinkedlist(head);
    head = insertafternode(head, second, 9);
    printf("after inserting elements in linked list......\n");
    Traversallinkedlist(head);

    return 0;
}
