#include <stdio.h>

#define MAX 100
#define INF 99999

void floydWarshall(int graph[MAX][MAX], int n)
{
    int dist[MAX][MAX];
    int i, j, k;

    // Copy graph into distance matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else if (graph[i][j] == 0)
                dist[i][j] = INF;
            else
                dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall Dynamic Programming
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print shortest path matrix
    printf("\nShortest Distance Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    // Check for negative cycle
    for (i = 0; i < n; i++)
    {
        if (dist[i][i] < 0)
        {
            printf("\nGraph contains a negative weight cycle.\n");
            return;
        }
    }
}

int main()
{
    int graph[MAX][MAX];
    int n;
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter the adjacency matrix:\n");
    printf("(Enter 0 if there is no edge)\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, n);

    return 0;
}