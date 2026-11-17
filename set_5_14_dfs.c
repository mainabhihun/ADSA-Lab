#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int color[MAX];
int discovery[MAX];
int finish[MAX];
int time = 0;
int n;

/*
    color:
    0 = WHITE (unvisited)
    1 = GRAY  (currently being visited)
    2 = BLACK (completely visited)
*/

void DFS_Visit(int u)
{
    int v;

    color[u] = 1;              // Mark as GRAY
    discovery[u] = ++time;

    for (v = 0; v < n; v++)
    {
        if (graph[u][v] == 1)
        {
            // Tree Edge
            if (color[v] == 0)
            {
                printf("%d -> %d : Tree Edge\n", u, v);
                DFS_Visit(v);
            }

            // Back Edge
            else if (color[v] == 1)
            {
                printf("%d -> %d : Back Edge\n", u, v);
            }

            // Forward or Cross Edge
            else if (color[v] == 2)
            {
                if (discovery[u] < discovery[v])
                    printf("%d -> %d : Forward Edge\n", u, v);
                else
                    printf("%d -> %d : Cross Edge\n", u, v);
            }
        }
    }

    color[u] = 2;              // Mark as BLACK
    finish[u] = ++time;
}

void DFS()
{
    int i;

    // Initialize
    for (i = 0; i < n; i++)
    {
        color[i] = 0;
        discovery[i] = 0;
        finish[i] = 0;
    }

    time = 0;

    // DFS for all vertices
    // This also handles disconnected graphs
    for (i = 0; i < n; i++)
    {
        if (color[i] == 0)
        {
            DFS_Visit(i);
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nDFS Edge Classification:\n");
    printf("------------------------\n");

    DFS();

    printf("\nVertex\tDiscovery\tFinish\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\n",
               i, discovery[i], finish[i]);
    }

    return 0;
}