#include <stdio.h>

#define MAX 20

int n, graph[MAX][MAX], path[MAX];

int isSafe(int v, int pos) {
    int i;

    if (!graph[path[pos - 1]][v])
        return 0;

    for (i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

int hamiltonian(int pos) {
    int v;

    if (pos == n)
        return graph[path[pos - 1]][path[0]];

    for (v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamiltonian(pos + 1))
                return 1;

            path[pos] = -1;
        }
    }

    return 0;
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

    for (i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0;

    if (hamiltonian(1)) {
        printf("Hamiltonian Cycle exists:\n");
        for (i = 0; i < n; i++)
            printf("%d -> ", path[i]);
        printf("0\n");
    } else {
        printf("Hamiltonian Cycle does not exist.\n");
    }

    return 0;
}