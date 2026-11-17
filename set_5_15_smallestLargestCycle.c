#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int path[MAX];

int n;
int isDirected;

int smallestCycle = MAX + 1;
int largestCycle = 0;

int smallPath[MAX];
int largePath[MAX];

/* Check whether vertex is already in current path */
int isInPath(int vertex, int pathLength)
{
    int i;

    for (i = 0; i < pathLength; i++)
    {
        if (path[i] == vertex)
            return 1;
    }

    return 0;
}

/* Copy current cycle to smallest cycle */
void saveSmallest(int pathLength)
{
    int i;

    for (i = 0; i < pathLength; i++)
        smallPath[i] = path[i];

    smallPath[pathLength] = path[0];
}

/* Copy current cycle to largest cycle */
void saveLargest(int pathLength)
{
    int i;

    for (i = 0; i < pathLength; i++)
        largePath[i] = path[i];

    largePath[pathLength] = path[0];
}

/*
   DFS to find all simple cycles
*/
void DFS(int start, int current, int pathLength)
{
    int next;

    for (next = 0; next < n; next++)
    {
        if (graph[current][next] == 0)
            continue;

        /* Found a cycle */
        if (next == start && pathLength >= 2)
        {
            int cycleLength = pathLength;

            /*
               For undirected graph, avoid counting
               the same cycle in reverse direction.
            */
            if (!isDirected)
            {
                if (pathLength >= 2 &&
                    path[1] > path[pathLength - 1])
                {
                    continue;
                }
            }

            if (cycleLength < smallestCycle)
            {
                smallestCycle = cycleLength;
                saveSmallest(pathLength);
            }

            if (cycleLength > largestCycle)
            {
                largestCycle = cycleLength;
                saveLargest(pathLength);
            }
        }

        /* Continue DFS if vertex is not already in path */
        else if (!isInPath(next, pathLength))
        {
            path[pathLength] = next;

            DFS(start, next, pathLength + 1);
        }
    }
}

/* Find cycles in the graph */
void findCycles()
{
    int start;
    int i;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    /*
       Start DFS from every vertex.
       Only start vertices that are the smallest
       vertex in the cycle are considered.
    */
    for (start = 0; start < n; start++)
    {
        path[0] = start;

        DFS(start, start, 1);
    }

    if (largestCycle == 0)
    {
        printf("\nNo cycle exists in the graph.\n");
        return;
    }

    printf("\nSmallest Cycle:\n");

    for (i = 0; i <= smallestCycle; i++)
    {
        printf("%d", smallPath[i]);

        if (i < smallestCycle)
            printf(" -> ");
    }

    printf("\nCycle length = %d\n", smallestCycle);

    printf("\nLargest Cycle:\n");

    for (i = 0; i <= largestCycle; i++)
    {
        printf("%d", largePath[i]);

        if (i < largestCycle)
            printf(" -> ");
    }

    printf("\nCycle length = %d\n", largestCycle);
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter 1 for Directed graph");
    printf("\nEnter 0 for Undirected graph");
    printf("\nChoice: ");
    scanf("%d", &isDirected);

    printf("\nEnter adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    findCycles();

    return 0;
}