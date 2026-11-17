#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *root;

/* Create Tree */
void createTree() {
    root = NULL;
}

/* Create new node */
struct Node* newNode(int x) {
    struct Node *n = malloc(sizeof(struct Node));

    n->data = x;
    n->color = RED;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;

    return n;
}

/* Get color */
int color(struct Node *n) {
    if (n == NULL)
        return BLACK;

    return n->color;
}

/* Left Rotation */
void leftRotate(struct Node *x) {
    struct Node *y = x->right;

    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

/* Right Rotation */
void rightRotate(struct Node *y) {
    struct Node *x = y->left;

    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/* Fix insertion */
void insertFix(struct Node *z) {

    while (z != root && color(z->parent) == RED) {

        if (z->parent == z->parent->parent->left) {

            struct Node *y = z->parent->parent->right;

            /* Case 1 */
            if (color(y) == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else {

                /* Case 2 */
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }

                /* Case 3 */
                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                rightRotate(z->parent->parent);
            }
        }

        else {

            struct Node *y = z->parent->parent->left;

            /* Case 1 */
            if (color(y) == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else {

                /* Case 2 */
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }

                /* Case 3 */
                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

/* Insert Item */
void insertItem(int x) {

    struct Node *z = newNode(x);
    struct Node *p = NULL;
    struct Node *q = root;

    /* Normal BST insertion */
    while (q != NULL) {

        p = q;

        if (x < q->data)
            q = q->left;
        else if (x > q->data)
            q = q->right;
        else {
            free(z);
            return;
        }
    }

    z->parent = p;

    if (p == NULL)
        root = z;
    else if (x < p->data)
        p->left = z;
    else
        p->right = z;

    insertFix(z);
}

/* Search Item */
struct Node* searchItem(int x) {

    struct Node *q = root;

    while (q != NULL) {

        if (x == q->data)
            return q;

        if (x < q->data)
            q = q->left;
        else
            q = q->right;
    }

    return NULL;
}

/* Minimum node */
struct Node* minimum(struct Node *p) {

    while (p->left != NULL)
        p = p->left;

    return p;
}

/* Transplant */
void transplant(struct Node *u, struct Node *v) {

    if (u->parent == NULL)
        root = v;

    else if (u == u->parent->left)
        u->parent->left = v;

    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

/* Fix deletion */
void deleteFix(struct Node *x, struct Node *parent) {

    while (x != root && color(x) == BLACK) {

        if (x == parent->left) {

            struct Node *w = parent->right;

            /* Case 1 */
            if (color(w) == RED) {

                w->color = BLACK;
                parent->color = RED;

                leftRotate(parent);

                w = parent->right;
            }

            /* Case 2 */
            if (color(w ? w->left : NULL) == BLACK &&
                color(w ? w->right : NULL) == BLACK) {

                if (w != NULL)
                    w->color = RED;

                x = parent;
                parent = x->parent;
            }

            else {

                /* Case 3 */
                if (color(w ? w->right : NULL) == BLACK) {

                    if (w && w->left)
                        w->left->color = BLACK;

                    if (w)
                        w->color = RED;

                    if (w)
                        rightRotate(w);

                    w = parent->right;
                }

                /* Case 4 */
                if (w)
                    w->color = parent->color;

                parent->color = BLACK;

                if (w && w->right)
                    w->right->color = BLACK;

                leftRotate(parent);

                x = root;
                parent = NULL;
            }
        }

        else {

            struct Node *w = parent->left;

            /* Case 1 */
            if (color(w) == RED) {

                w->color = BLACK;
                parent->color = RED;

                rightRotate(parent);

                w = parent->left;
            }

            /* Case 2 */
            if (color(w ? w->right : NULL) == BLACK &&
                color(w ? w->left : NULL) == BLACK) {

                if (w != NULL)
                    w->color = RED;

                x = parent;
                parent = x->parent;
            }

            else {

                /* Case 3 */
                if (color(w ? w->left : NULL) == BLACK) {

                    if (w && w->right)
                        w->right->color = BLACK;

                    if (w)
                        w->color = RED;

                    if (w)
                        leftRotate(w);

                    w = parent->left;
                }

                /* Case 4 */
                if (w)
                    w->color = parent->color;

                parent->color = BLACK;

                if (w && w->left)
                    w->left->color = BLACK;

                rightRotate(parent);

                x = root;
                parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;
}

/* Delete Item */
void deleteItem(int value) {

    struct Node *z = searchItem(value);

    if (z == NULL) {
        printf("Item not found\n");
        return;
    }

    struct Node *y = z;
    struct Node *x;
    struct Node *xParent;

    int oldColor = y->color;

    /* Node has no left child */
    if (z->left == NULL) {

        x = z->right;
        xParent = z->parent;

        transplant(z, z->right);
    }

    /* Node has no right child */
    else if (z->right == NULL) {

        x = z->left;
        xParent = z->parent;

        transplant(z, z->left);
    }

    /* Node has two children */
    else {

        y = minimum(z->right);
        oldColor = y->color;

        x = y->right;

        if (y->parent == z) {

            xParent = y;

            if (x != NULL)
                x->parent = y;
        }

        else {

            xParent = y->parent;

            transplant(y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);

        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    free(z);

    /* Fix only if deleted node was black */
    if (oldColor == BLACK)
        deleteFix(x, xParent);
}

/* Delete entire tree */
void deleteTree(struct Node *p) {

    if (p == NULL)
        return;

    deleteTree(p->left);
    deleteTree(p->right);

    free(p);
}

/* Inorder traversal */
void inorder(struct Node *p) {

    if (p == NULL)
        return;

    inorder(p->left);

    printf("%d(%s) ",
           p->data,
           p->color == RED ? "R" : "B");

    inorder(p->right);
}

/* Main */
int main() {

    createTree();

    insertItem(10);
    insertItem(20);
    insertItem(30);
    insertItem(15);
    insertItem(25);
    insertItem(5);
    insertItem(1);

    printf("Red-Black Tree:\n");
    inorder(root);

    if (searchItem(15))
        printf("\n15 found\n");
    else
        printf("\n15 not found\n");

    deleteItem(20);

    printf("After deleting 20:\n");
    inorder(root);

    deleteItem(10);

    printf("\nAfter deleting 10:\n");
    inorder(root);

    deleteTree(root);
    root = NULL;

    return 0;
}