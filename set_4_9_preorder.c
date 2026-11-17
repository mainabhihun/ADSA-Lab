#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void preorder(struct Node* root) {
    struct Node* stack[SIZE];
    int top = -1;

    if (root == NULL)
        return;

    stack[++top] = root;

    while (top != -1) {
        struct Node* temp = stack[top--];

        printf("%d ", temp->data);

        /* Push right first, then left */
        if (temp->right != NULL)
            stack[++top] = temp->right;

        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}

int main() {
    struct Node* root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Preorder Traversal: ");
    preorder(root);

    return 0;
}