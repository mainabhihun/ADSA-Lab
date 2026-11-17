#include <stdio.h>

int main()
{
    int n, amount, i, count;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin denominations in descending order:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter amount: ");
    scanf("%d", &amount);

    printf("\nCoins used: ");

    for (i = 0; i < n; i++)
    {
        count = amount / coins[i];

        if (count > 0)
        {
            printf("%d x %d  ", coins[i], count);
            amount = amount % coins[i];
        }
    }

    if (amount != 0)
        printf("\nExact change cannot be made.");
    else
        printf("\n");

    return 0;
}