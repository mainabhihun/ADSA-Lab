#include <stdio.h>

#define MAX 20

int n, e, m;
int graph[MAX][MAX];
int selected[MAX];

int isClique(int count) {
    int i, j;

    if (count == m)
        return 1;

    for (i = 0; i < n; i++) {
        if (!selected[i]) {
            int ok = 1;

            for (j = 0; j < n; j++)
                if (selected[j] && !graph[i][j])
                    ok = 0;

            if (ok) {
                selected[i] = 1;

                if (isClique(count + 1))
                    return 1;

                selected[i] = 0;
            }
        }
    }

    return 0;
}

int main() {
    int i, j;

    printf("Enter n, e and m: ");
    scanf("%d %d %d", &n, &e, &m);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges:\n", e);

    for (i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    if (isClique(0))
        printf("Graph contains a clique of size %d.\n", m);
    else
        printf("Graph does not contain a clique of size %d.\n", m);

    return 0;
}