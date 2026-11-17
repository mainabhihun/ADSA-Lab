#include <stdio.h>
#define MAX 20

int main() {
    int n, graph[MAX][MAX], indegree[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int i, j, count = 0;

    printf("Enter vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j])
                indegree[j]++;
        }

    for (i = 0; i < n; i++)
        if (indegree[i] == 0)
            queue[rear++] = i;

    printf("Topological Sort: ");

    while (front < rear) {
        int u = queue[front++];
        printf("%d ", u);
        count++;

        for (j = 0; j < n; j++) {
            if (graph[u][j]) {
                indegree[j]--;
                if (indegree[j] == 0)
                    queue[rear++] = j;
            }
        }
    }

    if (count != n)
        printf("\nGraph contains a cycle.");

    return 0;
}