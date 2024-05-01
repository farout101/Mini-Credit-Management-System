#ifndef AVL_TREE_H
#define AVL_TREE_H

// Define UserData structure
typedef struct {
    char name[50];
    char password[50];
    double credits;
    int isAdmin;
    char phoneNo[20];
} UserData;

// Define AVL tree node structure
typedef struct AVLNode {
    UserData* data; // Pointer to user data
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Function to insert user data into AVL tree
AVLNode* insertIntoAVL(AVLNode* root, UserData* userData);

// Function to perform in-order traversal of AVL tree and store sorted data in the file
void traverseAndStoreInOrder(AVLNode* root, FILE* file);

#endif /* AVL_TREE_H */
