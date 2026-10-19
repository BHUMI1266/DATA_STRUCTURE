#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int n;


void DFS(int v)
{
    int i;

    printf("%d ", v);

    visited[v] = 1;

    for (i = 0; i < n; i++)
    {
        if (graph[v][i] == 1 && visited[i] == 0)
        {
            DFS(i);
        }
    }
}


void BFS(int start)
{
    int queue[MAX];
    int front = 0, rear = 0;
    int i, v;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear)
    {
        v = queue[front++];
        printf("%d ", v);

        for (i = 0; i < n; i++)
        {
            if (graph[v][i] == 1 && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    int i, j, choice, start;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    do
    {
        printf("\n\n--- MENU ---");
        printf("\n1. DFS Traversal");
        printf("\n2. BFS Traversal");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                for (i = 0; i < n; i++)
                    visited[i] = 0;

                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);

                printf("DFS Traversal: ");
                DFS(start);
                break;

            case 2:
                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);

                printf("BFS Traversal: ");
                BFS(start);
                break;

            case 3:
                printf("Exiting program...");
                break;

            default:
                printf("Invalid choice!");
        }

    } while (choice != 3);

    return 0;
}
