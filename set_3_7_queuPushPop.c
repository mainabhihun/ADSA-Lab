#include <stdio.h>
#define MAX 5

int s1[MAX], s2[MAX];
int top1 = -1, top2 = -1;

/* Method 1: Push costly */
void enqueue1(int x) {
    while (top1 != -1)
        s2[++top2] = s1[top1--];

    s1[++top1] = x;

    while (top2 != -1)
        s1[++top1] = s2[top2--];
}

int dequeue1() {
    if (top1 == -1) {
        printf("Queue Empty\n");
        return -1;
    }
    return s1[top1--];
}

/* Method 2: Pop costly */
void enqueue2(int x) {
    s1[++top1] = x;
}

int dequeue2() {
    int x;

    if (top1 == -1 && top2 == -1) {
        printf("Queue Empty\n");
        return -1;
    }

    if (top2 == -1)
        while (top1 != -1)
            s2[++top2] = s1[top1--];

    x = s2[top2--];
    return x;
}

int main() {
    printf("Method 1: Push Costly\n");

    enqueue1(10);
    enqueue1(20);
    enqueue1(30);

    printf("Deleted: %d\n", dequeue1());
    printf("Deleted: %d\n", dequeue1());

    printf("\nMethod 2: Pop Costly\n");

    top1 = top2 = -1;

    enqueue2(10);
    enqueue2(20);
    enqueue2(30);

    printf("Deleted: %d\n", dequeue2());
    printf("Deleted: %d\n", dequeue2());

    return 0;
}