
#include <stdio.h>

#define SIZE 10

int bloom[SIZE] = {0};

/* Hash functions */
int hash1(int x)
{
    return x % SIZE;
}

int hash2(int x)
{
    return (x / SIZE + 3) % SIZE;
}

/* Allocation */
void allocate(int x)
{
    int h1 = hash1(x);
    int h2 = hash2(x);

    bloom[h1]++;
    bloom[h2]++;

    printf("Element allocated successfully!\n");
}

/* Deallocation */
void deallocate(int x)
{
    int h1 = hash1(x);
    int h2 = hash2(x);

    if (bloom[h1] > 0 && bloom[h2] > 0)
    {
        bloom[h1]--;
        bloom[h2]--;

        printf("Element deallocated successfully!\n");
    }
    else
    {
        printf("Element not found!\n");
    }
}

/* Display Bloom Filter */
void display()
{
    int i;

    printf("\nBloom Filter Counters:\n");

    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", bloom[i]);
    }

    printf("\n");
}

int main()
{
    int choice, x;

    do
    {
        printf("\n--- BLOOM FILTER MENU ---\n");
        printf("1. Allocation\n");
        printf("2. Deallocation\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter element: ");
                scanf("%d", &x);
                allocate(x);
                break;

            case 2:
                printf("Enter element: ");
                scanf("%d", &x);
                deallocate(x);
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
