#include <stdio.h>

void merge(int a[], int n, int size) {
    int temp[100], i, j, k, mid, end;

    for (i = 0; i < n; i += 2 * size) {
        mid = i + size;
        end = i + 2 * size;

        if (mid > n) mid = n;
        if (end > n) end = n;

        j = i;
        k = i;

        while (j < mid && mid < end) {
            if (a[j] < a[mid])
                temp[k++] = a[j++];
            else
                temp[k++] = a[mid++];
        }

        while (j < mid)
            temp[k++] = a[j++];

        while (mid < end)
            temp[k++] = a[mid++];

        for (j = i; j < end; j++)
            a[j] = temp[j];
    }
}

int main() {
    int a[100], n, i, size;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (size = 1; size < n; size *= 2)
        merge(a, n, size);

    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}