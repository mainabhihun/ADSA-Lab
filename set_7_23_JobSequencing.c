#include <stdio.h>

typedef struct
{
    char id;
    int deadline;
    int profit;
} Job;

void jobSequencing(Job jobs[], int n)
{
    int i, j, maxDeadline = 0;
    int slot[100];
    int totalProfit = 0;

    /* Find maximum deadline */
    for (i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;

    /* Sort jobs by decreasing profit */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (jobs[i].profit < jobs[j].profit)
            {
                Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    /* Initialize slots */
    for (i = 0; i <= maxDeadline; i++)
        slot[i] = -1;

    /* Schedule jobs */
    for (i = 0; i < n; i++)
    {
        for (j = jobs[i].deadline; j >= 1; j--)
        {
            if (slot[j] == -1)
            {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("\nJob Sequence: ");

    for (i = 1; i <= maxDeadline; i++)
    {
        if (slot[i] != -1)
            printf("%c ", jobs[slot[i]].id);
    }

    printf("\nMaximum Profit = %d\n", totalProfit);
}

int main()
{
    Job jobs[] =
    {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);

    return 0;
}