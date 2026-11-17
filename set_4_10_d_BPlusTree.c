#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

struct Node {
    int key[ORDER];
    struct Node *child[ORDER + 1];
    struct Node *next;
    int n;
    int leaf;
};

struct Node *root = NULL;

/* Create a new node */
struct Node* newNode(int leaf) {
    struct Node *p = malloc(sizeof(struct Node));

    p->n = 0;
    p->leaf = leaf;
    p->next = NULL;

    for (int i = 0; i <= ORDER; i++)
        p->child[i] = NULL;

    return p;
}

/* createTree */
void createTree() {
    root = NULL;
}

/* Search */
struct Node* searchItem(int x) {
    struct Node *p = root;

    if (p == NULL)
        return NULL;

    while (!p->leaf) {
        int i = 0;

        while (i < p->n && x >= p->key[i])
            i++;

        p = p->child[i];
    }

    for (int i = 0; i < p->n; i++)
        if (p->key[i] == x)
            return p;

    return NULL;
}

/* Find parent */
struct Node* findParent(struct Node *p, struct Node *child) {
    if (p == NULL || p->leaf)
        return NULL;

    for (int i = 0; i <= p->n; i++) {
        if (p->child[i] == child)
            return p;

        struct Node *q = findParent(p->child[i], child);

        if (q != NULL)
            return q;
    }

    return NULL;
}

/* Insert key into leaf */
void insertLeaf(struct Node *leaf, int x) {
    int i = leaf->n - 1;

    while (i >= 0 && leaf->key[i] > x) {
        leaf->key[i + 1] = leaf->key[i];
        i--;
    }

    leaf->key[i + 1] = x;
    leaf->n++;
}

/* Insert into parent */
void insertParent(struct Node *left, int key, struct Node *right) {
    struct Node *parent = findParent(root, left);

    /* Left is root */
    if (parent == NULL) {
        parent = newNode(0);

        parent->key[0] = key;
        parent->child[0] = left;
        parent->child[1] = right;
        parent->n = 1;

        root = parent;
        return;
    }

    int i = 0;

    while (i <= parent->n && parent->child[i] != left)
        i++;

    for (int j = parent->n; j >= i + 1; j--)
        parent->child[j + 1] = parent->child[j];

    for (int j = parent->n - 1; j >= i; j--)
        parent->key[j + 1] = parent->key[j];

    parent->key[i] = key;
    parent->child[i + 1] = right;
    parent->n++;

    /* Split parent if full */
    if (parent->n == ORDER) {
        int tempKey[ORDER];
        struct Node *tempChild[ORDER + 1];

        for (int j = 0; j < ORDER; j++)
            tempKey[j] = parent->key[j];

        for (int j = 0; j <= ORDER; j++)
            tempChild[j] = parent->child[j];

        struct Node *rightParent = newNode(0);

        int mid = ORDER / 2;

        parent->n = mid;

        for (int j = 0; j <= mid; j++)
            parent->child[j] = tempChild[j];

        for (int j = 0; j < mid; j++)
            parent->key[j] = tempKey[j];

        int k = 0;

        for (int j = mid + 1; j <= ORDER; j++)
            rightParent->child[k++] = tempChild[j];

        k = 0;

        for (int j = mid + 1; j < ORDER; j++)
            rightParent->key[k++] = tempKey[j];

        rightParent->n = ORDER - mid - 1;

        insertParent(parent, tempKey[mid], rightParent);
    }
}

/* insertItem */
void insertItem(int x) {
    if (searchItem(x) != NULL)
        return;

    if (root == NULL) {
        root = newNode(1);
        root->key[0] = x;
        root->n = 1;
        return;
    }

    struct Node *leaf = root;

    while (!leaf->leaf) {
        int i = 0;

        while (i < leaf->n && x >= leaf->key[i])
            i++;

        leaf = leaf->child[i];
    }

    insertLeaf(leaf, x);

    /* Leaf overflow */
    if (leaf->n == ORDER) {
        struct Node *right = newNode(1);

        int mid = ORDER / 2;

        right->n = ORDER - mid;

        for (int i = 0; i < right->n; i++)
            right->key[i] = leaf->key[mid + i];

        leaf->n = mid;

        right->next = leaf->next;
        leaf->next = right;

        insertParent(leaf, right->key[0], right);
    }
}

/* Update parent separator */
void updateParentKey(struct Node *node) {
    struct Node *parent = findParent(root, node);

    if (parent == NULL)
        return;

    int pos = 0;

    while (parent->child[pos] != node)
        pos++;

    if (pos > 0) {
        struct Node *p = node;

        while (!p->leaf)
            p = p->child[0];

        parent->key[pos - 1] = p->key[0];
    }

    updateParentKey(parent);
}

/* Remove child from parent */
void removeChild(struct Node *parent, int pos) {
    for (int i = pos; i < parent->n; i++)
        parent->key[i - 1] = parent->key[i];

    for (int i = pos; i < parent->n; i++)
        parent->child[i] = parent->child[i + 1];

    parent->n--;
}

/* Delete item */
void deleteItem(int x) {
    struct Node *leaf = searchItem(x);

    if (leaf == NULL) {
        printf("Item not found\n");
        return;
    }

    int pos = 0;

    while (leaf->key[pos] != x)
        pos++;

    for (int i = pos; i < leaf->n - 1; i++)
        leaf->key[i] = leaf->key[i + 1];

    leaf->n--;

    /* Root leaf */
    if (leaf == root) {
        if (leaf->n == 0) {
            free(root);
            root = NULL;
        }
        return;
    }

    /* Minimum keys = 2 for order 4 */
    if (leaf->n >= 2) {
        updateParentKey(leaf);
        return;
    }

    struct Node *parent = findParent(root, leaf);

    int index = 0;

    while (parent->child[index] != leaf)
        index++;

    /* Borrow from left sibling */
    if (index > 0 && parent->child[index - 1]->n > 2) {
        struct Node *left = parent->child[index - 1];

        for (int i = leaf->n; i > 0; i--)
            leaf->key[i] = leaf->key[i - 1];

        leaf->key[0] = left->key[left->n - 1];

        left->n--;

        updateParentKey(leaf);
        return;
    }

    /* Borrow from right sibling */
    if (index < parent->n &&
        parent->child[index + 1]->n > 2) {

        struct Node *right = parent->child[index + 1];

        leaf->key[leaf->n] = right->key[0];
        leaf->n++;

        for (int i = 0; i < right->n - 1; i++)
            right->key[i] = right->key[i + 1];

        right->n--;

        updateParentKey(right);
        return;
    }

    /* Merge with left */
    if (index > 0) {
        struct Node *left = parent->child[index - 1];

        for (int i = 0; i < leaf->n; i++)
            left->key[left->n++] = leaf->key[i];

        left->next = leaf->next;

        free(leaf);

        removeChild(parent, index);

    }
    /* Merge with right */
    else {
        struct Node *right = parent->child[index + 1];

        for (int i = 0; i < right->n; i++)
            leaf->key[leaf->n++] = right->key[i];

        leaf->next = right->next;

        free(right);

        removeChild(parent, index + 1);
    }

    /* Parent becomes empty */
    if (parent == root && parent->n == 0) {
        root = parent->child[0];
        free(parent);
    }
}

/* Display B+ Tree */
void display() {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    struct Node *p = root;

    while (!p->leaf)
        p = p->child[0];

    while (p != NULL) {
        for (int i = 0; i < p->n; i++)
            printf("%d ", p->key[i]);

        p = p->next;
    }
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
    insertItem(25);

    printf("B+ Tree: ");
    display();

    if (searchItem(12))
        printf("\n12 found");
    else
        printf("\n12 not found");

    deleteItem(12);

    printf("\nAfter deleting 12: ");
    display();

    deleteItem(6);

    printf("\nAfter deleting 6: ");
    display();

    deleteTree(root);
    root = NULL;

    return 0;
}