#include <stdio.h>
#include <stdlib.h>

#define N 4
#define MAX 10000

typedef struct {
    int a[16];
    int cost, level;
} Node;

Node pq[MAX];
int size = 0;

int heuristic(int a[]) {
    int h = 0, i, x, r, c;

    for (i = 0; i < 16; i++) {
        if (a[i] == 0) continue;

        x = a[i] - 1;
        r = i / 4;
        c = i % 4;

        h += abs(r - x / 4) + abs(c - x % 4);
    }

    return h;
}

void push(Node x) {
    int i = size++;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (pq[p].cost <= x.cost)
            break;

        pq[i] = pq[p];
        i = p;
    }

    pq[i] = x;
}

Node pop() {
    Node root = pq[0], x = pq[--size];
    int i = 0;

    while (2 * i + 1 < size) {
        int c = 2 * i + 1;

        if (c + 1 < size && pq[c + 1].cost < pq[c].cost)
            c++;

        if (x.cost <= pq[c].cost)
            break;

        pq[i] = pq[c];
        i = c;
    }

    pq[i] = x;
    return root;
}

void print(int a[]) {
    int i;

    for (i = 0; i < 16; i++) {
        printf("%2d ", a[i]);
        if (i % 4 == 3)
            printf("\n");
    }
}

void solve(int start[]) {
    int goal[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0
    };

    Node cur, next;
    int i, pos, r, c, nr, nc;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (i = 0; i < 16; i++)
        cur.a[i] = start[i];

    cur.level = 0;
    cur.cost = heuristic(cur.a);
    push(cur);

    while (size) {
        cur = pop();

        for (i = 0; i < 16; i++)
            if (cur.a[i] != goal[i])
                break;

        if (i == 16) {
            printf("\nSolution found:\n");
            print(cur.a);
            return;
        }

        for (pos = 0; pos < 16; pos++)
            if (cur.a[pos] == 0)
                break;

        r = pos / 4;
        c = pos % 4;

        for (i = 0; i < 4; i++) {
            nr = r + dr[i];
            nc = c + dc[i];

            if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
                next = cur;
                next.a[pos] = next.a[nr * 4 + nc];
                next.a[nr * 4 + nc] = 0;

                next.level++;
                next.cost = next.level + heuristic(next.a);

                push(next);
            }
        }
    }

    printf("No solution found.\n");
}

int main() {
    int puzzle[16], i;

    printf("Enter the 15-puzzle:\n");

    for (i = 0; i < 16; i++)
        scanf("%d", &puzzle[i]);

    solve(puzzle);

    return 0;
}