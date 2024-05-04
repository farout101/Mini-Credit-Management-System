#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char name[50];
    char password[50];
    double credits;
    int isAdmin;
    int isBan;
    char phoneNo[20];
};

struct Transition {
    int id;
    char sender[50];
    char receiver[50];
    double amount;
    char timestamp[20];
};

// AVL tree node 
struct AVLNode {
    void *data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

int height(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new AVL node
struct AVLNode *newNode(void *data) {
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate subtree rooted with y
struct AVLNode *rightRotate(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
struct AVLNode *leftRotate(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Insert a new node into the AVL tree
struct AVLNode *insert(struct AVLNode *node, void *data, int (*compare)(const void *, const void *)) {
    // Perform standard BST insertion
    if (node == NULL)
        return newNode(data);

    if (compare(data, node->data) < 0)
        node->left = insert(node->left, data, compare);
    else if (compare(data, node->data) > 0)
        node->right = insert(node->right, data, compare);
    else // Equal keys are not allowed in AVL
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && compare(data, node->left->data) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && compare(data, node->right->data) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && compare(data, node->left->data) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && compare(data, node->right->data) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// In-order traversal to fill the array with sorted data
void inOrderTraversal(struct AVLNode *root, void **sortedArray, int *index) {
    if (root != NULL) {
        inOrderTraversal(root->left, sortedArray, index);
        sortedArray[(*index)++] = root->data;
        inOrderTraversal(root->right, sortedArray, index);
    }
}

// Compare function for Users based on name
int compareUsers(const void *a, const void *b) {
    return strcmp(((const struct User *)a)->name, ((const struct User *)b)->name);
}

// Compare function for Transitions based on timestamp
int compareTransitions(const void *a, const void *b) {
    return strcmp(((const struct Transition *)a)->timestamp, ((const struct Transition *)b)->timestamp);
}

struct User **sortUsers(struct User *users, int numUsers) {
    struct AVLNode *root = NULL;
    struct User **sortedUsers = malloc(numUsers * sizeof(struct User *));
    int i, index = 0;
    for (i = 0; i < numUsers; i++)
        root = insert(root, &users[i], compareUsers);
    inOrderTraversal(root, (void **)sortedUsers, &index);
    return sortedUsers;
}

struct Transition **sortTransitions(struct Transition *transitions, int numTransitions) {
    struct AVLNode *root = NULL;
    struct Transition **sortedTransitions = malloc(numTransitions * sizeof(struct Transition *));
    int i, index = 0;
    for (i = 0; i < numTransitions; i++)
        root = insert(root, &transitions[i], compareTransitions);
    inOrderTraversal(root, (void **)sortedTransitions, &index);
    return sortedTransitions;
}