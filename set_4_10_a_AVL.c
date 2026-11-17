#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data, height;
    struct Node *left, *right;
};

int height(struct Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct Node* createNode(int x) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = x;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int balance(struct Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

/* createTree */
struct Node* createTree() {
    return NULL;
}

/* insertItem */
struct Node* insertItem(struct Node *root, int x) {
    if (root == NULL)
        return createNode(x);

    if (x < root->data)
        root->left = insertItem(root->left, x);
    else if (x > root->data)
        root->right = insertItem(root->right, x);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && x < root->left->data)
        return rightRotate(root);

    if (b < -1 && x > root->right->data)
        return leftRotate(root);

    if (b > 1 && x > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && x < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* minNode(struct Node *root) {
    while (root->left)
        root = root->left;
    return root;
}

/* deleteItem */
struct Node* deleteItem(struct Node *root, int x) {
    if (root == NULL)
        return NULL;

    if (x < root->data)
        root->left = deleteItem(root->left, x);
    else if (x > root->data)
        root->right = deleteItem(root->right, x);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node *temp = root->left ?
                                root->left : root->right;

            if (temp == NULL) {
                free(root);
                return NULL;
            } else {
                *root = *temp;
                free(temp);
            }
        } else {
            struct Node *temp = minNode(root->right);
            root->data = temp->data;
            root->right = deleteItem(root->right, temp->data);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && balance(root->left) >= 0)
        return rightRotate(root);

    if (b > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && balance(root->right) <= 0)
        return leftRotate(root);

    if (b < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* searchItem */
struct Node* searchItem(struct Node *root, int x) {
    if (root == NULL || root->data == x)
        return root;

    if (x < root->data)
        return searchItem(root->left, x);

    return searchItem(root->right, x);
}

/* deleteTree */
void deleteTree(struct Node *root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void inorder(struct Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct Node *root = createTree();

    root = insertItem(root, 30);
    root = insertItem(root, 20);
    root = insertItem(root, 10);
    root = insertItem(root, 40);
    root = insertItem(root, 50);

    printf("AVL Tree: ");
    inorder(root);

    if (searchItem(root, 40))
        printf("\n40 found");

    root = deleteItem(root, 20);

    printf("\nAfter deletion: ");
    inorder(root);

    deleteTree(root);

    return 0;
}