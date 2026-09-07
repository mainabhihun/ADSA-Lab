#include <stdio.h>
#include <stdlib.h>

/* ---------- Insertion Sort ---------- */
void insertionSort(int a[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/* ---------- Bubble Sort ---------- */
void bubbleSort(int a[], int n) {
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

/* ---------- Selection Sort ---------- */
void selectionSort(int a[], int n) {
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++) {
        min = i;

        for (j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

/* ---------- Shell Sort ---------- */
void shellSort(int a[], int n) {
    int gap, i, j, temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = a[i];

            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];

            a[j] = temp;
        }
    }
}

/* ---------- Quick Sort ---------- */
void quickSort(int a[], int low, int high) {
    int i, j, pivot, temp;

    i = low;
    j = high;
    pivot = a[(low + high) / 2];

    while (i <= j) {
        while (a[i] < pivot)
            i++;

        while (a[j] > pivot)
            j--;

        if (i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if (low < j)
        quickSort(a, low, j);

    if (i < high)
        quickSort(a, i, high);
}

/* ---------- Merge Sort ---------- */
void merge(int a[], int low, int mid, int high) {
    int temp[100], i, j, k;

    i = low;
    j = mid + 1;
    k = low;

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

void mergeSort(int a[], int low, int high) {
    int mid;

    if (low < high) {
        mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

/* ---------- Heap Sort ---------- */
void heapify(int a[], int n, int i) {
    int largest, left, right, temp;

    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n) {
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (i = n - 1; i > 0; i--) {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

/* ---------- Radix Sort ---------- */
void radixSort(int a[], int n) {
    int output[100], count[10];
    int max, exp, i;

    max = a[0];

    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    for (exp = 1; max / exp > 0; exp *= 10) {

        for (i = 0; i < 10; i++)
            count[i] = 0;

        for (i = 0; i < n; i++)
            count[(a[i] / exp) % 10]++;

        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (i = n - 1; i >= 0; i--)
            output[--count[(a[i] / exp) % 10]] = a[i];

        for (i = 0; i < n; i++)
            a[i] = output[i];
    }
}

/* ---------- Counting Sort ---------- */
void countingSort(int a[], int n) {
    int count[1000] = {0};
    int i, j, max = a[0];

    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    for (i = 0; i < n; i++)
        count[a[i]]++;

    j = 0;

    for (i = 0; i <= max; i++) {
        while (count[i] > 0) {
            a[j++] = i;
            count[i]--;
        }
    }
}

/* ---------- Bucket Sort ---------- */
void bucketSort(int a[], int n) {
    int bucket[10][100];
    int count[10] = {0};
    int i, j, k, index, temp;

    for (i = 0; i < n; i++) {
        index = a[i] / 10;

        if (index > 9)
            index = 9;

        bucket[index][count[index]++] = a[i];
    }

    for (i = 0; i < 10; i++) {
        for (j = 1; j < count[i]; j++) {
            temp = bucket[i][j];
            k = j - 1;

            while (k >= 0 && bucket[i][k] > temp) {
                bucket[i][k + 1] = bucket[i][k];
                k--;
            }

            bucket[i][k + 1] = temp;
        }
    }

    k = 0;

    for (i = 0; i < 10; i++)
        for (j = 0; j < count[i]; j++)
            a[k++] = bucket[i][j];
}

/* ---------- Radix Exchange Sort ---------- */
void radixExchange(int a[], int left, int right, int bit) {
    int i, j, temp;

    if (left >= right || bit < 0)
        return;

    i = left;
    j = right;

    while (i <= j) {
        while (i <= right && !(a[i] & (1 << bit)))
            i++;

        while (j >= left && (a[j] & (1 << bit)))
            j--;

        if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
            j--;
        }
    }

    radixExchange(a, left, j, bit - 1);
    radixExchange(a, i, right, bit - 1);
}

/* ---------- Address Calculation Sort ---------- */
void addressCalculationSort(int a[], int n) {
    int table[1000];
    int i, j, index;

    for (i = 0; i < 1000; i++)
        table[i] = -1;

    for (i = 0; i < n; i++) {
        index = a[i];

        while (table[index] != -1)
            index++;

        table[index] = a[i];
    }

    j = 0;

    for (i = 0; i < 1000; i++) {
        if (table[i] != -1)
            a[j++] = table[i];
    }
}

/* ---------- Display Array ---------- */
void display(int a[], int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

/* ---------- Main Program ---------- */
int main() {
    int a[100], n, choice, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid size!\n");
        return 0;
    }

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    do {
        printf("\n========== SORTING MENU ==========\n");
        printf("1. Insertion Sort\n");
        printf("2. Bubble Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Shell Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Merge Sort\n");
        printf("7. Heap Sort\n");
        printf("8. Radix Sort\n");
        printf("9. Counting Sort\n");
        printf("10. Bucket Sort\n");
        printf("11. Radix Exchange Sort\n");
        printf("12. Address Calculation Sort\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                insertionSort(a, n);
                printf("Sorted using Insertion Sort:\n");
                display(a, n);
                break;

            case 2:
                bubbleSort(a, n);
                printf("Sorted using Bubble Sort:\n");
                display(a, n);
                break;

            case 3:
                selectionSort(a, n);
                printf("Sorted using Selection Sort:\n");
                display(a, n);
                break;

            case 4:
                shellSort(a, n);
                printf("Sorted using Shell Sort:\n");
                display(a, n);
                break;

            case 5:
                quickSort(a, 0, n - 1);
                printf("Sorted using Quick Sort:\n");
                display(a, n);
                break;

            case 6:
                mergeSort(a, 0, n - 1);
                printf("Sorted using Merge Sort:\n");
                display(a, n);
                break;

            case 7:
                heapSort(a, n);
                printf("Sorted using Heap Sort:\n");
                display(a, n);
                break;

            case 8:
                radixSort(a, n);
                printf("Sorted using Radix Sort:\n");
                display(a, n);
                break;

            case 9:
                countingSort(a, n);
                printf("Sorted using Counting Sort:\n");
                display(a, n);
                break;

            case 10:
                bucketSort(a, n);
                printf("Sorted using Bucket Sort:\n");
                display(a, n);
                break;

            case 11:
                radixExchange(a, 0, n - 1, 30);
                printf("Sorted using Radix Exchange Sort:\n");
                display(a, n);
                break;

            case 12:
                addressCalculationSort(a, n);
                printf("Sorted using Address Calculation Sort:\n");
                display(a, n);
                break;

            case 13:
                printf("Program ended.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 13);

    return 0;
}