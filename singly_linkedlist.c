#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

/* INSERT NODE */
void insert(struct Node **head, int value)
{
    struct Node *newNode, *temp;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->next = NULL;

    /* Insert at beginning */
    if (*head == NULL || value < (*head)->data)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        temp = *head;

        /* Find correct position */
        while (temp->next != NULL &&
               temp->next->data < value)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    printf("\nNode inserted successfully.");
}
/* DELETE NODE */
void deleteNode(struct Node **head, int value)
{
    struct Node *temp, *prev;

    if (*head == NULL) {
        printf("\nLinked List is empty!");
        return;
    }

    temp = *head;
    prev = NULL;

    if (temp->data == value) {
        *head = temp->next;
        free(temp);

        printf("\nNode deleted successfully.");
        return;
    }

    
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }


    if (temp == NULL) {
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
    struct Node *temp = head;

    if (head == NULL) {
        printf("\nLinked List is empty!");
        return;
    }

    printf("\nLinked List: ");

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main()
{
    struct Node *head = NULL;
    int choice;
    int value;

    while (1) {

        printf("\n\n--- MENU ---");
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Display");
        printf("\n4. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

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
