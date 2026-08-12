#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int DQ[MAX];


int main()
{
    int choice, ele, removed;
    int *front = (int *)malloc(sizeof(int));
    int *rear = (int *)malloc(sizeof(int));

	void DQ_Insert(int *, int *, int);
	int DQ_Delete(int *, int *);
	void DQ_Display(int *, int *);


	*front = -1;
    *rear = -1;

    while (1) 
	{
        printf("\n=== Double Queue Menu ===");
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Display");
        printf("\n4. Exit");
       
		printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
		{   
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                DQ_Insert(front, rear, ele);
                break;
            case 2:
                removed = DQ_Delete(front, rear);
                if (removed != -1)
                    printf("Removed value: %d\n", removed);
                break;
            case 3:
                DQ_Display(front, rear);
                break;
            case 4:
                printf("Exiting program.\n");
                free(front);
                free(rear);
                exit(0);
            
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

void DQ_Insert(int *front, int *rear, int ele) 
{
    if (*rear >= MAX - 1) 
	{
        printf("Queue is full.\n");
        return;
    }

    if (*front == -1 && *rear == -1) 
	{
        *front = *rear = 0;
    } 
	else 
	{
        (*rear)++;
    }

    DQ[*rear] = ele;
    printf("Inserted: %d\n", ele);
}

int DQ_Delete(int *front, int *rear) 
{
    int choice;	
    int removed;
    if (*front == -1 || *front > *rear) 
	{
        printf("Queue is empty.\n");
        return -1;
    }

    printf("Enter 1 to delete from Front, 2 to delete from Rear: ");
    scanf("%d", &choice);

    if (choice == 1) {
        removed = DQ[*front];
        (*front)++;
    } 
	else if (choice == 2) 
	{
        removed = DQ[*rear];
        (*rear)--;
    } 
	else 
	{
        printf("Invalid delete choice.\n");
        return -1;
    }

    if (*front > *rear)
        *front = *rear = -1;

    return removed;
}

void DQ_Display(int *front, int *rear) 
{
	int i;
	int choice;
    if (*front == -1 || *front > *rear) 
	{
        printf("Queue is empty.\n");
        return;
    }

    
    printf("Enter 1 to display from Front, 2 to display from Rear: ");
    scanf("%d", &choice);

    printf("Queue contents:\n");
    if (choice == 1) 
	{
        for ( i = *front; i <= *rear; i++) 
		{
            printf("%d ", DQ[i]);
        }
    } 
	else if (choice == 2) 
	{
        for ( i = *rear; i >= *front; i--) 
		{
            printf("%d ", DQ[i]);
        }
    } 
	else 
	{
        printf("Invalid display choice.\n");
    }
    printf("\n");
}