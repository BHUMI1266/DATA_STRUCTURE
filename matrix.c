#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *right;
    struct Node *down;
};

int main()
{
    int r, c;

    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    if (r <= 0 || c <= 0)
    {
        printf("Invalid matrix size!\n");
        return 0;
    }

    struct Node *head = NULL;
    struct Node *rowStart = NULL;
    struct Node *prevRow = NULL;

    for (int i = 0; i < r; i++)
    {
        struct Node *prev = NULL;
        rowStart = NULL;

        for (int j = 0; j < c; j++)
        {
            struct Node *newNode = malloc(sizeof(struct Node));

            if (newNode == NULL)
            {
                printf("Memory allocation failed!\n");
                return 1;
            }

            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &newNode->data);

            newNode->right = NULL;
            newNode->down = NULL;

            if (head == NULL)
            {
                head = newNode;
            }

            if (rowStart == NULL)
            {
                rowStart = newNode;
            }

            if (prev != NULL)
            {
                prev->right = newNode;
            }

            if (prevRow != NULL)
            {
                struct Node *upper = prevRow;

                for (int k = 0; k < j; k++)
                {
                    upper = upper->right;
                }

                upper->down = newNode;
            }

            prev = newNode;
        }

        prevRow = prevRow == NULL ? rowStart : prevRow;

        if (i > 0)
        {
            struct Node *temp = prevRow;

            for (int k = 0; k < i - 1; k++)
            {
                temp = temp->down;
            }
        }
    }

    printf("\nMatrix:\n");

    struct Node *row = head;

    while (row != NULL)
    {
        struct Node *temp = row;

        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->right;
        }

        printf("\n");
        row = row->down;
    }

    return 0;
}