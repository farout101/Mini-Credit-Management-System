#include "avl_tree.h"
#include <stdlib.h>
#include <string.h>

// Function to create a new AVL tree node
AVLNode* createNode(UserData* userData) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (newNode != NULL) {
        newNode->data = userData;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
    }
    return newNode;
}

// Function to get the height of a node
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to get the balance factor of a node
int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Function to perform right rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// Function to perform left rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// Function to insert user data into AVL tree
AVLNode* insertIntoAVL(AVLNode* root, UserData* userData) {
    // Perform standard BST insertion
    if (root == NULL) {
        return createNode(userData);
    }

    if (strcmp(userData->name, root->data->name) < 0) {
        root->left = insertIntoAVL(root->left, userData);
    } else if (strcmp(userData->name, root->data->name) > 0) {
        root->right = insertIntoAVL(root->right, userData);
    } else { // Duplicate keys are not allowed
        return root;
    }

    // Update height of this ancestor node
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && strcmp(userData->name, root->left->data->name) < 0) {
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && strcmp(userData->name, root->right->data->name) > 0) {
        return leftRotate(root);
    }

    // Left Right Case
    if (balance > 1 && strcmp(userData->name, root->left->data->name) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && strcmp(userData->name, root->right->data->name) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the (unchanged) node pointer
    return root;
}

// Function to perform in-order traversal of AVL tree and store sorted data in the file
void traverseAndStoreInOrder(AVLNode* root, FILE* file) {
    if (root != NULL) {
        traverseAndStoreInOrder(root->left, file);
        fprintf(file, "%s %s %.2lf %d %s\n", root->data->name, root->data->password, root->data->credits, root->data->isAdmin, root->data->phoneNo);
        traverseAndStoreInOrder(root->right, file);
    }
}
