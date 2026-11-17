#include <stdio.h>
#include <limits.h>

#define MAX 100

void prim(int graph[MAX][MAX], int n)
{
    int parent[MAX];
    int key[MAX];
    int mstSet[MAX];

    int i, j;

    // Initialize arrays
    for (i = 0; i < n; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = 0;
        parent[i] = -1;
    }

    // Start from vertex 0
    key[0] = 0;

    // Find MST
    for (i = 0; i < n - 1; i++)
    {
        int min = INT_MAX;
        int u = -1;

        // Find vertex with minimum key value
        for (j = 0; j < n; j++)
        {
            if (!mstSet[j] && key[j] < min)
            {
                min = key[j];
                u = j;
            }
        }

        // Add vertex to MST
        mstSet[u] = 1;

        // Update adjacent vertices
        for (j = 0; j < n; j++)
        {
            if (graph[u][j] != 0 &&
                !mstSet[j] &&
                graph[u][j] < key[j])
            {
                parent[j] = u;
                key[j] = graph[u][j];
            }
        }
    }

    // Print MST
    int totalCost = 0;

    printf("\nEdges in Minimum Spanning Tree:\n");
    printf("Edge\tWeight\n");

    for (i = 1; i < n; i++)
    {
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }

    printf("\nTotal cost of MST = %d\n", totalCost);
}

int main()
{
    int graph[MAX][MAX];
    int n;
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    printf("(Enter 0 if there is no edge)\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    prim(graph, n);

    return 0;
}