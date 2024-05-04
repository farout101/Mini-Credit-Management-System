#ifndef AVL_TREE_H
#define AVL_TREE_H

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

struct AVLNode {
    void *data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

int height(struct AVLNode *node);
int max(int a, int b);
struct AVLNode *newNode(void *data);
struct AVLNode *rightRotate(struct AVLNode *y);
struct AVLNode *leftRotate(struct AVLNode *x);
int getBalance(struct AVLNode *node);
struct AVLNode *insert(struct AVLNode *node, void *data, int (*compare)(const void *, const void *));
void inOrderTraversal(struct AVLNode *root, void **sortedArray, int *index);
int compareUsers(const void *a, const void *b);
int compareTransitions(const void *a, const void *b);
struct User **sortUsers(struct User *users, int numUsers);
struct Transition **sortTransitions(struct Transition *transitions, int numTransitions);

#endif
