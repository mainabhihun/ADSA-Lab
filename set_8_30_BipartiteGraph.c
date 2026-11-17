#include <stdio.h>

#define MAX 20

int n, graph[MAX][MAX], color[MAX];

int isBipartite() {
    int queue[MAX], front, rear, i, j;

    for (i = 0; i < n; i++)
        color[i] = -1;

    for (i = 0; i < n; i++) {
        if (color[i] != -1)
            continue;

        front = rear = 0;
        queue[rear++] = i;
        color[i] = 0;

        while (front < rear) {
            int u = queue[front++];
            for (j = 0; j < n; j++) {
                if (graph[u][j]) {
                    if (color[j] == -1) {
                        color[j] = 1 - color[u];
                        queue[rear++] = j;
                    }
                    else if (color[j] == color[u])
                        return 0;
                }
            }
        }
    }
    return 1;
}

int main() {
    int e, i, u, v;
    printf("Enter n and e: ");
    scanf("%d %d", &n, &e);
    printf("Enter %d edges:\n", e);
    for (i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }
    if (isBipartite())
        printf("Graph is Bipartite.\n");
    else
        printf("Graph is not Bipartite.\n");
    return 0;
}