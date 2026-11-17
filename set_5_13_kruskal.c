#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an edge
struct Edge
{
    int source;
    int destination;
    int weight;
};

// Compare function for sorting edges
int compare(const void *a, const void *b)
{
    struct Edge *edge1 = (struct Edge *)a;
    struct Edge *edge2 = (struct Edge *)b;

    return edge1->weight - edge2->weight;
}

// Find the parent of a vertex
int find(int parent[], int vertex)
{
    if (parent[vertex] == vertex)
        return vertex;

    return find(parent, parent[vertex]);
}

// Union of two sets
void unionSets(int parent[], int rank[], int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY)
    {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Kruskal's Algorithm
void kruskal(struct Edge edges[], int V, int E)
{
    struct Edge result[MAX];
    int parent[MAX];
    int rank[MAX];

    int i, count = 0;
    int totalWeight = 0;

    // Initialize each vertex as its own set
    for (i = 0; i < V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges by weight
    qsort(edges, E, sizeof(struct Edge), compare);

    printf("\nEdges in Minimum Spanning Tree:\n");
    printf("Edge\tWeight\n");

    // Process edges
    for (i = 0; i < E && count < V - 1; i++)
    {
        int u = edges[i].source;
        int v = edges[i].destination;

        int rootU = find(parent, u);
        int rootV = find(parent, v);

        // Add edge if it doesn't create a cycle
        if (rootU != rootV)
        {
            result[count] = edges[i];

            printf("%d - %d\t%d\n",
                   edges[i].source,
                   edges[i].destination,
                   edges[i].weight);

            totalWeight += edges[i].weight;
            count++;

            unionSets(parent, rank, rootU, rootV);
        }
    }

    printf("\nTotal cost of MST = %d\n", totalWeight);
}

int main()
{
    
    int V, E;
    struct Edge edges[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("\nEnter edges (source destination weight):\n");

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d",
              &edges[i].source,
              &edges[i].destination,
              &edges[i].weight);
    }

    kruskal(edges, V, E);

    return 0;
}