#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct SplayNode
{
    int key;
    struct SplayNode *left;
    struct SplayNode *right;
} SplayNode;

// Function to create a new node
SplayNode *newNode(int key)
{
    SplayNode *node = (SplayNode *)malloc(sizeof(SplayNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Right rotate
SplayNode *rightRotate(SplayNode *x)
{
    SplayNode *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotate
SplayNode *leftRotate(SplayNode *x)
{
    SplayNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation
SplayNode *splay(SplayNode *root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key)
    {
        if (root->left == NULL)
            return root;
        if (root->left->key > key)
        {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key)
        {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else
    {
        if (root->right == NULL)
            return root;
        if (root->right->key > key)
        {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)
        {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Insert operation
SplayNode *insert(SplayNode *root, int key)
{
    if (root == NULL)
        return newNode(key);
    root = splay(root, key);
    if (root->key == key)
        return root;

    SplayNode *new_node = newNode(key);
    if (root->key > key)
    {
        new_node->right = root;
        new_node->left = root->left;
        root->left = NULL;
    }
    else
    {
        new_node->left = root;
        new_node->right = root->right;
        root->right = NULL;
    }
    return new_node;
}

// Delete operation
SplayNode *deleteNode(SplayNode *root, int key)
{
    if (root == NULL)
        return NULL;
    root = splay(root, key);
    if (root->key != key)
        return root;

    SplayNode *temp;
    if (root->left == NULL)
    {
        temp = root;
        root = root->right;
    }
    else
    {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    free(temp);
    return root;
}

// Search operation
SplayNode *search(SplayNode *root, int key)
{
    return splay(root, key);
}

// Utility function to print pre-order traversal
void preOrder(SplayNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Main function to test the splay tree
int main()
{
    SplayNode *root = NULL;

    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 200);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 150);
    root = insert(root, 250);

    printf("Pre-order traversal of the splay tree is: ");
    preOrder(root);
    printf("\n");

    root = deleteNode(root, 50);
    printf("Pre-order traversal after deleting 50: ");
    preOrder(root);
    printf("\n");

    root = search(root, 150);
    printf("Pre-order traversal after searching for 150: ");
    preOrder(root);
    printf("\n");

    return 0;
}
