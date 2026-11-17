#include <stdio.h>

#define MAX 100
#define INF 99999

struct Edge {
    int src;
    int dest;
    int weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int source)
{
    int dist[MAX];
    int i, j;

    // Initialize distances
    for (i = 0; i < V; i++)
        dist[i] = INF;

    dist[source] = 0;

    // Relax all edges V-1 times
    for (i = 1; i <= V - 1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative-weight cycle
    for (j = 0; j < E; j++)
    {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            printf("\nGraph contains a negative weight cycle.\n");
            return;
        }
    }

    // Print shortest distances
    printf("\nShortest distances from vertex %d:\n", source);
    printf("Vertex\tDistance\n");

    for (i = 0; i < V; i++)
    {
        if (dist[i] == INF)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, dist[i]);
    }
}

int main()
{
    int V, E, source;
    struct Edge edges[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("\nEnter edges (source destination weight):\n");

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    bellmanFord(edges, V, E, source);

    return 0;
}