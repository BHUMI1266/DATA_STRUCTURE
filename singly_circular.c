#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

/* INSERT NODE */
void insert(struct Node **head, int value)
{
    struct Node *newNode, *temp;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;

    if (*head == NULL)
    {
        *head = newNode;
        newNode->next = *head;
    }
    else
    {
        temp = *head;

      
        while (temp->next != *head)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = *head;
    }

    printf("\nNode inserted successfully.");
}

/* DELETE NODE */
void deleteNode(struct Node **head, int value)
{
    struct Node *temp, *prev;

    /* Empty list */
    if (*head == NULL)
    {
        printf("\nLinked List is empty!");
        return;
    }

    temp = *head;
    prev = NULL;

    /* Delete first node */
    if (temp->data == value)
    {
        /* Only one node */
        if (temp->next == *head)
        {
            *head = NULL;
            free(temp);
        }
        else
        {
            /* Find last node */
            prev = *head;

            while (prev->next != *head)
            {
                prev = prev->next;
            }

            *head = temp->next;
            prev->next = *head;

            free(temp);
        }

        printf("\nNode deleted successfully.");
        return;
    }

    /* Search node */
    prev = *head;
    temp = temp->next;

    while (temp != *head && temp->data != value)
    {
        prev = temp;
        temp = temp->next;
    }

    /* Node not found */
    if (temp == *head)
    {
        printf("\nNode not found!");
        return;
    }

    /* Delete node */
    prev->next = temp->next;
    free(temp);

    printf("\nNode deleted successfully.");
}

/* DISPLAY */
void display(struct Node *head)
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("\nLinked List is empty!");
        return;
    }

    temp = head;

    printf("\nCircular Linked List: ");

    do
    {
        printf("%d -> ", temp->data);
        temp = temp->next;

    } while (temp != head);

    printf("(HEAD)\n");
}

/* MAIN */
int main()
{
    struct Node *head = NULL;

    int choice;
    int value;

    while (1)
    {
        printf("\n\n--- MENU ---");
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Display");
        printf("\n4. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter data: ");
                scanf("%d", &value);

                insert(&head, value);
                break;

            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &value);

                deleteNode(&head, value);
                break;

            case 3:
                display(head);
                break;

            case 4:
                printf("\nProgram ended.");
                return 0;

            default:
                printf("\nInvalid choice!");
        }
    }

    return 0;
}