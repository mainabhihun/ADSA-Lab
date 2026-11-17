#include <stdio.h>
#include <stdlib.h>

#define T 3

struct Node {
    int key[2 * T - 1];
    struct Node *child[2 * T];
    int n;
    int leaf;
};

struct Node *root = NULL;

/* Create a new node */
struct Node* createNode(int leaf) {
    struct Node *p = malloc(sizeof(struct Node));

    p->leaf = leaf;
    p->n = 0;

    for (int i = 0; i < 2 * T; i++)
        p->child[i] = NULL;

    return p;
}

/* createTree */
void createTree() {
    root = NULL;
}

/* searchItem */
struct Node* searchItem(struct Node *p, int x) {
    if (p == NULL)
        return NULL;

    int i = 0;

    while (i < p->n && x > p->key[i])
        i++;

    if (i < p->n && x == p->key[i])
        return p;

    if (p->leaf)
        return NULL;

    return searchItem(p->child[i], x);
}

/* Split child */
void splitChild(struct Node *p, int i) {
    struct Node *y = p->child[i];
    struct Node *z = createNode(y->leaf);

    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->key[j] = y->key[j + T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->child[j] = y->child[j + T];
    }

    y->n = T - 1;

    for (int j = p->n; j >= i + 1; j--)
        p->child[j + 1] = p->child[j];

    p->child[i + 1] = z;

    for (int j = p->n - 1; j >= i; j--)
        p->key[j + 1] = p->key[j];

    p->key[i] = y->key[T - 1];
    p->n++;
}

/* Insert into non-full node */
void insertNonFull(struct Node *p, int x) {
    int i = p->n - 1;

    if (p->leaf) {

        while (i >= 0 && x < p->key[i]) {
            p->key[i + 1] = p->key[i];
            i--;
        }

        p->key[i + 1] = x;
        p->n++;
    }
    else {

        while (i >= 0 && x < p->key[i])
            i--;

        i++;

        if (p->child[i]->n == 2 * T - 1) {

            splitChild(p, i);

            if (x > p->key[i])
                i++;
        }

        insertNonFull(p->child[i], x);
    }
}

/* insertItem */
void insertItem(int x) {

    if (searchItem(root, x))
        return;

    if (root == NULL) {
        root = createNode(1);
        root->key[0] = x;
        root->n = 1;
        return;
    }

    if (root->n == 2 * T - 1) {

        struct Node *s = createNode(0);

        s->child[0] = root;
        root = s;

        splitChild(s, 0);

        insertNonFull(s, x);
    }
    else {
        insertNonFull(root, x);
    }
}

/* Get predecessor */
int predecessor(struct Node *p, int idx) {
    struct Node *cur = p->child[idx];

    while (!cur->leaf)
        cur = cur->child[cur->n];

    return cur->key[cur->n - 1];
}

/* Get successor */
int successor(struct Node *p, int idx) {
    struct Node *cur = p->child[idx + 1];

    while (!cur->leaf)
        cur = cur->child[0];

    return cur->key[0];
}

/* Borrow from previous child */
void borrowFromPrev(struct Node *p, int idx) {

    struct Node *child = p->child[idx];
    struct Node *sibling = p->child[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->key[i + 1] = child->key[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->child[i + 1] = child->child[i];
    }

    child->key[0] = p->key[idx - 1];

    if (!child->leaf)
        child->child[0] = sibling->child[sibling->n];

    p->key[idx - 1] = sibling->key[sibling->n - 1];

    child->n++;
    sibling->n--;
}

/* Borrow from next child */
void borrowFromNext(struct Node *p, int idx) {

    struct Node *child = p->child[idx];
    struct Node *sibling = p->child[idx + 1];

    child->key[child->n] = p->key[idx];

    if (!child->leaf)
        child->child[child->n + 1] = sibling->child[0];

    p->key[idx] = sibling->key[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->key[i - 1] = sibling->key[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->child[i - 1] = sibling->child[i];
    }

    child->n++;
    sibling->n--;
}

/* Merge two children */
void merge(struct Node *p, int idx) {

    struct Node *child = p->child[idx];
    struct Node *sibling = p->child[idx + 1];

    child->key[T - 1] = p->key[idx];

    for (int i = 0; i < sibling->n; i++)
        child->key[i + T] = sibling->key[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->child[i + T] = sibling->child[i];
    }

    for (int i = idx + 1; i < p->n; i++)
        p->key[i - 1] = p->key[i];

    for (int i = idx + 2; i <= p->n; i++)
        p->child[i - 1] = p->child[i];

    child->n += sibling->n + 1;
    p->n--;

    free(sibling);
}

/* Fill child if it has fewer than T-1 keys */
void fill(struct Node *p, int idx) {

    if (idx != 0 && p->child[idx - 1]->n >= T)
        borrowFromPrev(p, idx);

    else if (idx != p->n && p->child[idx + 1]->n >= T)
        borrowFromNext(p, idx);

    else {

        if (idx != p->n)
            merge(p, idx);
        else
            merge(p, idx - 1);
    }
}

/* Delete from leaf/internal node */
void deleteFromNode(struct Node *p, int x) {

    int idx = 0;

    while (idx < p->n && p->key[idx] < x)
        idx++;

    /* Key found */
    if (idx < p->n && p->key[idx] == x) {

        if (p->leaf) {

            for (int i = idx + 1; i < p->n; i++)
                p->key[i - 1] = p->key[i];

            p->n--;
        }
        else {

            if (p->child[idx]->n >= T) {

                int pred = predecessor(p, idx);

                p->key[idx] = pred;

                deleteFromNode(p->child[idx], pred);
            }
            else if (p->child[idx + 1]->n >= T) {

                int succ = successor(p, idx);

                p->key[idx] = succ;

                deleteFromNode(p->child[idx + 1], succ);
            }
            else {

                merge(p, idx);

                deleteFromNode(p->child[idx], x);
            }
        }
    }
    else {

        if (p->leaf)
            return;

        int flag = (idx == p->n);

        if (p->child[idx]->n < T)
            fill(p, idx);

        if (flag && idx > p->n)
            deleteFromNode(p->child[idx - 1], x);
        else
            deleteFromNode(p->child[idx], x);
    }
}

/* deleteItem */
void deleteItem(int x) {

    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    if (searchItem(root, x) == NULL) {
        printf("Item not found\n");
        return;
    }

    deleteFromNode(root, x);

    /* Root becomes empty */
    if (root->n == 0) {

        struct Node *temp = root;

        if (root->leaf)
            root = NULL;
        else
            root = root->child[0];

        free(temp);
    }
}

/* Display */
void display(struct Node *p) {

    if (p == NULL)
        return;

    int i;

    for (i = 0; i < p->n; i++) {

        if (!p->leaf)
            display(p->child[i]);

        printf("%d ", p->key[i]);
    }

    if (!p->leaf)
        display(p->child[i]);
}

/* deleteTree */
void deleteTree(struct Node *p) {

    if (p == NULL)
        return;

    if (!p->leaf) {

        for (int i = 0; i <= p->n; i++)
            deleteTree(p->child[i]);
    }

    free(p);
}

/* Main */
int main() {

    createTree();

    insertItem(10);
    insertItem(20);
    insertItem(5);
    insertItem(6);
    insertItem(12);
    insertItem(30);
    insertItem(7);
    insertItem(17);

    printf("B-Tree: ");
    display(root);

    if (searchItem(root, 12))
        printf("\n12 found");
    else
        printf("\n12 not found");

    deleteItem(6);

    printf("\nAfter deleting 6: ");
    display(root);

    deleteItem(12);

    printf("\nAfter deleting 12: ");
    display(root);

    deleteTree(root);
    root = NULL;

    return 0;
}