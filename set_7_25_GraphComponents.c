#include <stdio.h>

#define MAX 20

int n;
int graph[MAX][MAX];

/* ---------- Strongly Connected Components ---------- */

int visited[MAX];

void DFS1(int v)
{
    int i;
    visited[v] = 1;

    for (i = 0; i < n; i++)
        if (graph[v][i] && !visited[i])
            DFS1(i);
}

void DFS2(int v, int transpose[MAX][MAX])
{
    int i;
    visited[v] = 1;
    printf("%d ", v);

    for (i = 0; i < n; i++)
        if (transpose[v][i] && !visited[i])
            DFS2(i, transpose);
}

void SCC()
{
    int i, j;
    int transpose[MAX][MAX];

    /* Find finishing order */
    for (i = 0; i < n; i++)
        visited[i] = 0;

    for (i = 0; i < n; i++)
        if (!visited[i])
            DFS1(i);

    /* Transpose graph */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            transpose[i][j] = graph[j][i];

    /*
       For simplicity, perform Kosaraju using
       repeated search for vertices not yet printed.
    */
    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nStrongly Connected Components:\n");

    for (i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            printf("{ ");
            DFS2(i, transpose);
            printf("}\n");
        }
    }
}

/* ---------- Articulation Points and Bridges ---------- */

int disc[MAX], low[MAX], parent[MAX];
int timeCount;
int articulation[MAX];

void APBridgeDFS(int u)
{
    int v;
    int children = 0;

    disc[u] = low[u] = ++timeCount;

    for (v = 0; v < n; v++)
    {
        /* Treat directed graph as undirected */
        if (graph[u][v] || graph[v][u])
        {
            if (!disc[v])
            {
                children++;
                parent[v] = u;

                APBridgeDFS(v);

                if (low[v] < low[u])
                    low[u] = low[v];

                /* Articulation point */
                if (parent[u] == -1 && children > 1)
                    articulation[u] = 1;

                if (parent[u] != -1 && low[v] >= disc[u])
                    articulation[u] = 1;

                /* Bridge */
                if (low[v] > disc[u])
                    printf("Bridge: %d - %d\n", u, v);
            }
            else if (v != parent[u] && disc[v] < low[u])
            {
                low[u] = disc[v];
            }
        }
    }
}

void findAPBridges()
{
    int i;

    timeCount = 0;

    for (i = 0; i < n; i++)
    {
        disc[i] = 0;
        low[i] = 0;
        parent[i] = -1;
        articulation[i] = 0;
    }

    printf("\nBridges:\n");

    for (i = 0; i < n; i++)
        if (!disc[i])
            APBridgeDFS(i);

    printf("\nArticulation Points:\n");

    for (i = 0; i < n; i++)
        if (articulation[i])
            printf("%d ", i);

    printf("\n");
}

/* ---------- Biconnected Components ---------- */

int stackU[MAX * MAX];
int stackV[MAX * MAX];
int top = -1;

void BCCDFS(int u)
{
    int v;

    disc[u] = low[u] = ++timeCount;

    for (v = 0; v < n; v++)
    {
        if (!(graph[u][v] || graph[v][u]))
            continue;

        if (!disc[v])
        {
            stackU[++top] = u;
            stackV[top] = v;

            parent[v] = u;
            BCCDFS(v);

            if (low[v] < low[u])
                low[u] = low[v];

            if (low[v] >= disc[u])
            {
                printf("{ ");

                while (1)
                {
                    int a = stackU[top];
                    int b = stackV[top--];

                    printf("(%d-%d) ", a, b);

                    if (a == u && b == v)
                        break;
                }

                printf("}\n");
            }
        }
        else if (v != parent[u] && disc[v] < disc[u])
        {
            stackU[++top] = u;
            stackV[top] = v;

            if (disc[v] < low[u])
                low[u] = disc[v];
        }
    }
}

void findBCC()
{
    int i;

    timeCount = 0;
    top = -1;

    for (i = 0; i < n; i++)
    {
        disc[i] = 0;
        low[i] = 0;
        parent[i] = -1;
    }

    printf("\nBiconnected Components:\n");

    for (i = 0; i < n; i++)
        if (!disc[i])
            BCCDFS(i);
}

/* ---------- Main ---------- */

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix of directed graph:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    SCC();
    findBCC();
    findAPBridges();

    return 0;
}