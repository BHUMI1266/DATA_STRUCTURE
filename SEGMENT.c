#include <stdio.h>

#define MAX 100

int arr[MAX];
int tree[4 * MAX];
int n;

void build(int node, int start, int end)
{
    int mid; 

    if (start == end)
    {
        tree[node] = arr[start];
        return;
    }

    mid = (start + end) / 2;

    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}


int query(int node, int start, int end, int l, int r)
{
    int mid;
    int left;
    int right;

    if (r < start || end < l)
        return 0;

    if (l <= start && end <= r)
        return tree[node];

    mid = (start + end) / 2;

    left = query(2 * node, start, mid, l, r);
    right = query(2 * node + 1, mid + 1, end, l, r);

    return left + right;
}


void delete_element(int node, int start, int end, int idx)
{
    int mid;

 
    if (start == end)
    {
        arr[idx] = 0;     
        tree[node] = 0;    
        return;
    }

    mid = (start + end) / 2;


    if (idx <= mid)
        delete_element(2 * node, start, mid, idx);
    else
        delete_element(2 * node + 1, mid + 1, end, idx);


    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void display_array()
{
    int i;
    printf("Current Array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int ch, l, r, idx;
    int i; 

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Enter array elements:\n");

   
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    build(1, 0, n - 1);

    while (1)
    {
        printf("\n--- SEGMENT TREE ---\n");
        printf("1. Range Sum Query\n");
        printf("2. Delete Element\n");
        printf("3. Display\n");
		printf("4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                printf("Enter range (l r): ");
                scanf("%d %d", &l, &r);

                if (l < 0 || r >= n || l > r)
                {
                    printf("Invalid range.\n");
                    break;
                }

                printf("Range Sum = %d\n", query(1, 0, n - 1, l, r));
                break;

            case 2:
                printf("Enter index to delete: ");
                scanf("%d", &idx);

                if (idx < 0 || idx >= n)
                {
                    printf("Invalid index.\n");
                    break;
                }

                delete_element(1, 0, n - 1, idx);
                printf("Element at index %d deleted (Set to 0).\n", idx);
                break;

			case 3:
              
                display_array();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
