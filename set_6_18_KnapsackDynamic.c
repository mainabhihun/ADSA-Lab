#include <stdio.h>

#define MAX 100

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void knapsack(int weights[], int values[], int n, int capacity)
{
    int dp[MAX + 1][MAX + 1];
    int i, w;

    // Initialize DP table
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= capacity; w++)
        {
            // No items or zero capacity
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }

            // Current item can fit
            else if (weights[i - 1] <= w)
            {
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                );
            }

            // Current item cannot fit
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("\nMaximum profit = %d\n", dp[n][capacity]);

    // Find selected items
    printf("Selected items: ");

    w = capacity;

    for (i = n; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            printf("%d ", i);
            w = w - weights[i - 1];
        }
    }

    printf("\n");
}

int main()
{
    int n, capacity;
    int weights[MAX], values[MAX];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights of items:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &weights[i]);
    }

    printf("Enter values of items:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &values[i]);
    }

    printf("Enter capacity of knapsack: ");
    scanf("%d", &capacity);

    knapsack(weights, values, n, capacity);

    return 0;
}