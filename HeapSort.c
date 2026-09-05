#include <stdio.h>

// Heapify function
void heapify(int a[], int n, int i)
{
    int max = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    int temp;

    // lc child is larger than root
    if(lc < n && a[lc] > a[max])
    {
        max = lc;
    }

    //  rc child is larger than max
    if(rc < n && a[rc] > a[max])
    {
        max = rc;
    }

    // If max is not root
    if(max != i)
    {
        temp = a[i];
        a[i] = a[max];
        a[max] = temp;

        // Heapify the affected subtree
        heapify(a, n, max);
    }
}

// Heap Sort function
void heapSort(int a[], int n)
{
    int i, temp;

    // Build Max Heap
    for(i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }

    // Extract elements from heap
    for(i = n - 1; i > 0; i--)
    {
        // Move max element to the end
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        // Heapify remaining elements
        heapify(a, i, 0);
    }
}

int main()
{
    int a[100];
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: \n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    heapSort(a, n);

    printf("Sorted elements: ");

    for(i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}