#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 20

int n, cost[MAX][MAX], visited[MAX];
int minCost;

void tsp(int city, int count, int total) {
    int i;

    if (count == n) {
        if (cost[city][0] > 0)
            if (total + cost[city][0] < minCost)
                minCost = total + cost[city][0];
        return;
    }

    for (i = 0; i < n; i++) {
        if (!visited[i] && cost[city][i] > 0) {
            visited[i] = 1;
            tsp(i, count + 1, total + cost[city][i]);
            visited[i] = 0;
        }
    }
}

int main() {
    int i, j;
    clock_t start, end;
    double time_taken;

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    for (i = 0; i < n; i++)
        visited[i] = 0;

    minCost = INT_MAX;
    visited[0] = 1;

    start = clock();
    tsp(0, 1, 0);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nMinimum tour cost = %d", minCost);
    printf("\nExecution time = %f seconds\n", time_taken);

    return 0;
}