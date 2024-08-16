#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    int npl;
    struct node *left;
    struct node *right;
} Node;

Node *merge(Node *h1, Node *h2)
{
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;

    if (h1->data > h2->data)
    {
        Node *temp = h1;
        h1 = h2;
        h2 = temp;
    }

    h1->right = merge(h1->right, h2);

    if (h1->left == NULL)
    {
        h1->left = h1->right;
        h1->right = NULL;
        h1->npl = 0;
    }
    else
    {
        if (h1->left->npl < h1->right->npl)
        {
            Node *temp = h1->left;
            h1->left = h1->right;
            h1->right = temp;
        }
        h1->npl = h1->right->npl + 1;
    }

    return h1;
}

Node *insert(Node *root, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->npl = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    return merge(root, newNode);
}

Node *deleteMin(Node *root)
{
    if (root == NULL)
        return NULL;

    Node *left = root->left;
    Node *right = root->right;

    free(root);

    return merge(left, right);
}

void print(Node *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    print(root->left);
    print(root->right);
}

int main()
{
    Node *root = NULL;

    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 8);
    root = insert(root, 2);
    root = insert(root, 6);

    print(root);
    printf("\n");

    root = deleteMin(root);
    print(root);
    printf("\n");

    return 0;
}