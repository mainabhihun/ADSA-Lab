#include <stdio.h>

#define MAX 100

int n, capacity;
int weights[MAX], values[MAX];

int maxProfit = 0;
int currentProfit = 0;
int currentWeight = 0;

int selected[MAX];
int bestSelected[MAX];

void knapsack(int index)
{
    // If all items are considered
    if (index == n)
    {
        if (currentProfit > maxProfit)
        {
            maxProfit = currentProfit;

            for (int i = 0; i < n; i++)
                bestSelected[i] = selected[i];
        }

        return;
    }

    // Include current item if it fits
    if (currentWeight + weights[index] <= capacity)
    {
        selected[index] = 1;

        currentWeight += weights[index];
        currentProfit += values[index];

        knapsack(index + 1);

        // Backtrack
        currentWeight -= weights[index];
        currentProfit -= values[index];
        selected[index] = 0;
    }

    // Exclude current item
    selected[index] = 0;
    knapsack(index + 1);
}

int main()
{
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

    // Initialize
    for (int i = 0; i < n; i++)
    {
        selected[i] = 0;
        bestSelected[i] = 0;
    }

    // Start backtracking
    knapsack(0);

    printf("\nMaximum Profit = %d\n", maxProfit);

    printf("Selected Items: ");

    for (int i = 0; i < n; i++)
    {
        if (bestSelected[i])
            printf("%d ", i + 1);
    }

    printf("\n");

    printf("Selected item details:\n");

    for (int i = 0; i < n; i++)
    {
        if (bestSelected[i])
        {
            printf("Item %d: Weight = %d, Value = %d\n",
                   i + 1, weights[i], values[i]);
        }
    }

    return 0;
}