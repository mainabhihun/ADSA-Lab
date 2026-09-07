#include <stdio.h>

typedef struct {
    int low, high;
} Stack;

void merge(int a[], int low, int mid, int high) {
    int temp[100], i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low; i <= high; i++)
        a[i] = temp[i];
}

int main() {
    int a[100], n, i;
    Stack s[100];
    int top = -1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    /* Push initial range */
    s[++top].low = 0;
    s[top].high = n - 1;

    while (top >= 0) {
        int low = s[top].low;
        int high = s[top].high;
        top--;

        if (low < high) {
            int mid = (low + high) / 2;

            /* Push right and left parts */
            s[++top].low = mid + 1;
            s[top].high = high;

            s[++top].low = low;
            s[top].high = mid;
        }
    }

    /* Merge bottom-up */
    for (int size = 1; size < n; size *= 2)
        for (i = 0; i < n - size; i += 2 * size) {
            int mid = i + size - 1;
            int high = i + 2 * size - 1;

            if (high >= n)
                high = n - 1;

            merge(a, i, mid, high);
        }

    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}