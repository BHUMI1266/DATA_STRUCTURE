#include <stdio.h>
#include <stdlib.h>

struct Node
{
int data;
struct Node *right;
struct Node *down;
};

struct Node *createMatrix(int r, int c)
{
struct Node ***m = malloc(r * sizeof(struct Node **));

```
if (m == NULL)
    return NULL;

for (int i = 0; i < r; i++)
{
    m[i] = malloc(c * sizeof(struct Node *));

    if (m[i] == NULL)
        return NULL;
}

for (int i = 0; i < r; i++)
{
    for (int j = 0; j < c; j++)
    {
        m[i][j] = malloc(sizeof(struct Node));

        if (m[i][j] == NULL)
            return NULL;

        printf("Enter element [%d][%d]: ", i, j);
        scanf("%d", &m[i][j]->data);

        m[i][j]->right = NULL;
        m[i][j]->down = NULL;
    }
}

for (int i = 0; i < r; i++)
{
    for (int j = 0; j < c; j++)
    {
        if (j + 1 < c)
            m[i][j]->right = m[i][j + 1];

        if (i + 1 < r)
            m[i][j]->down = m[i + 1][j];
    }
}

struct Node *head = m[0][0];

/* Matrix values are linked; free only the pointer table */
for (int i = 0; i < r; i++)
    free(m[i]);

free(m);

return head;


}

void display(struct Node *head, int r, int c)
{
struct Node *row = head;

```
for (int i = 0; i < r; i++)
{
    struct Node *temp = row;

    for (int j = 0; j < c; j++)
    {
        printf("%d ", temp->data);
        temp = temp->right;
    }

    printf("\n");
    row = row->down;
}
```

}

int main()
{
int r, c;

```
printf("Enter rows and columns: ");
scanf("%d %d", &r, &c);

if (r <= 0 || c <= 0)
    return 0;

printf("\nEnter Matrix A:\n");
struct Node *A = createMatrix(r, c);

printf("\nEnter Matrix B:\n");
struct Node *B = createMatrix(r, c);

if (A == NULL || B == NULL)
    return 1;

struct Node *rowA = A;
struct Node *rowB = B;

printf("\nAddition Result:\n");

for (int i = 0; i < r; i++)
{
    struct Node *a = rowA;
    struct Node *b = rowB;

    for (int j = 0; j < c; j++)
    {
        printf("%d ", a->data + b->data);
        a = a->right;
        b = b->right;
    }

    printf("\n");
    rowA = rowA->down;
    rowB = rowB->down;
}

return 0;

}
