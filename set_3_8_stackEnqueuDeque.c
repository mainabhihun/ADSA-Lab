#include <stdio.h>

#define SIZE 100

typedef struct {
    int data[SIZE];
    int front, rear;
} Queue;

void init(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front > q->rear;
}

void enqueue(Queue *q, int x) {
    q->data[++q->rear] = x;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

/* Method 1: EnQueue costly */
void push1(Queue *q1, Queue *q2, int x) {
    enqueue(q2, x);

    while (!isEmpty(q1))
        enqueue(q2, dequeue(q1));

    while (!isEmpty(q2))
        enqueue(q1, dequeue(q2));
}

int pop1(Queue *q) {
    if (isEmpty(q))
        return -1;
    return dequeue(q);
}

/* Method 2: DeQueue costly */
void push2(Queue *q1, int x) {
    enqueue(q1, x);
}

int pop2(Queue *q1, Queue *q2) {
    if (isEmpty(q1))
        return -1;

    while (q1->front < q1->rear)
        enqueue(q2, dequeue(q1));

    int x = dequeue(q1);

    while (!isEmpty(q2))
        enqueue(q1, dequeue(q2));

    return x;
}

int main() {
    Queue q1, q2;

    /* Method 1 */
    init(&q1);
    init(&q2);

    push1(&q1, &q2, 10);
    push1(&q1, &q2, 20);
    push1(&q1, &q2, 30);

    printf("Method 1 Pop: %d\n", pop1(&q1));
    printf("Method 1 Pop: %d\n", pop1(&q1));

    /* Method 2 */
    init(&q1);
    init(&q2);

    push2(&q1, 10);
    push2(&q1, 20);
    push2(&q1, 30);

    printf("Method 2 Pop: %d\n", pop2(&q1, &q2));
    printf("Method 2 Pop: %d\n", pop2(&q1, &q2));

    return 0;
}