#include <stdio.h>
#include <stdlib.h>

/* Multilinked-list node: right connects columns, down connects rows */
struct Node
{
    int data;
    struct Node *right;
    struct Node *down;
};

/* Create a matrix using nodes connected by right and down pointers.
   The pointer table is used for easy access while building/calculating. */
struct Node ***createMatrix(int rows, int cols)
{
    struct Node ***matrix = malloc(rows * sizeof(struct Node **));

    if (matrix == NULL)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof(struct Node *));
        if (matrix[i] == NULL)
        {
            for (int k = 0; k < i; k++)
                free(matrix[k]);
            free(matrix);
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = malloc(sizeof(struct Node));

            if (matrix[i][j] == NULL)
            {
                for (int a = 0; a <= i; a++)
                {
                    int limit = (a == i) ? j : cols;
                    for (int b = 0; b < limit; b++)
                        free(matrix[a][b]);
                }

                for (int a = 0; a < rows; a++)
                    free(matrix[a]);
                free(matrix);
                return NULL;
            }

            matrix[i][j]->data = 0;
            matrix[i][j]->right = NULL;
            matrix[i][j]->down = NULL;
        }
    }

    /* Connect each node to the next node in its row and column. */
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j + 1 < cols)
                matrix[i][j]->right = matrix[i][j + 1];

            if (i + 1 < rows)
                matrix[i][j]->down = matrix[i + 1][j];
        }
    }

    return matrix;
}

void inputMatrix(struct Node ***matrix, int rows, int cols, char name)
{
    printf("\nEnter Matrix %c:\n", name);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]->data);
        }
    }
}

void displayMatrix(struct Node ***matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]->data);

        printf("\n");
    }
}

void addMatrices(struct Node ***A, struct Node ***B,
                 struct Node ***C, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            C[i][j]->data = A[i][j]->data + B[i][j]->data;
    }
}

void multiplyMatrices(struct Node ***A, struct Node ***B,
                      struct Node ***C, int rowsA, int colsA, int colsB)
{
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            int sum = 0;

            for (int k = 0; k < colsA; k++)
                sum += A[i][k]->data * B[k][j]->data;

            C[i][j]->data = sum;
        }
    }
}

void freeMatrix(struct Node ***matrix, int rows, int cols)
{
    if (matrix == NULL)
        return;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            free(matrix[i][j]);

        free(matrix[i]);
    }

    free(matrix);
}

int main(void)
{
    int choice;
    int r1, c1, r2, c2;
    struct Node ***A = NULL;
    struct Node ***B = NULL;
    struct Node ***C = NULL;

    printf("MULTILINKED LIST: MATRIX ADDITION AND MULTIPLICATION\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1)
        return 1;

    if (choice != 1 && choice != 2)
    {
        printf("Invalid choice!\n");
        return 0;
    }

    printf("Enter rows and columns of Matrix A: ");
    if (scanf("%d %d", &r1, &c1) != 2 || r1 <= 0 || c1 <= 0)
    {
        printf("Invalid matrix size!\n");
        return 0;
    }

    printf("Enter rows and columns of Matrix B: ");
    if (scanf("%d %d", &r2, &c2) != 2 || r2 <= 0 || c2 <= 0)
    {
        printf("Invalid matrix size!\n");
        return 0;
    }

    if (choice == 1 && (r1 != r2 || c1 != c2))
    {
        printf("Addition is not possible. Both matrices must have the same dimensions.\n");
        return 0;
    }

    if (choice == 2 && c1 != r2)
    {
        printf("Multiplication is not possible. Columns of A must equal rows of B.\n");
        return 0;
    }

    A = createMatrix(r1, c1);
    B = createMatrix(r2, c2);
    C = createMatrix(r1, (choice == 1) ? c1 : c2);

    if (A == NULL || B == NULL || C == NULL)
    {
        printf("Memory allocation failed!\n");
        freeMatrix(A, r1, c1);
        freeMatrix(B, r2, c2);
        freeMatrix(C, r1, (choice == 1) ? c1 : c2);
        return 1;
    }

    inputMatrix(A, r1, c1, 'A');
    inputMatrix(B, r2, c2, 'B');

    if (choice == 1)
    {
        addMatrices(A, B, C, r1, c1);
        printf("\nAddition Result:\n");
        displayMatrix(C, r1, c1);
    }
    else
    {
        multiplyMatrices(A, B, C, r1, c1, c2);
        printf("\nMultiplication Result:\n");
        displayMatrix(C, r1, c2);
    }

    freeMatrix(A, r1, c1);
    freeMatrix(B, r2, c2);
    freeMatrix(C, r1, (choice == 1) ? c1 : c2);

    return 0;
}
