#include <stdio.h>

void insertionSort(int arr[], int n)
{
    int key, j;

    // Base condition
    if (n <= 1)
        return;

    // Sort first n-1 elements
    insertionSort(arr, n - 1);

    // Insert the last element
    key = arr[n - 1];
    j = n - 2;

    while (j >= 0 && arr[j] > key)
    {
        arr[j + 1] = arr[j];
        j--;
    }

    arr[j + 1] = key;
}

int main()
{
    int arr[10], n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    insertionSort(arr, n);

    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
	printf("\n");
    return 0;
}