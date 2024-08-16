#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

typedef struct node *tree;

tree create_tree()
{
    tree t = (tree)malloc(sizeof(tree));
    t = NULL;
    return t;
}

int height(tree t)
{
    if (t == NULL)
        return -1;
    else
    {
        int lheight = height(t->left);
        int rheight = height(t->right);
        if (lheight > rheight)
            return lheight + 1;
        else
            return rheight + 1;
    }
}

tree left_rotation(tree t)
{
    tree temp = t->right;
    t->right = temp->left;
    temp->left = t;
    return temp;
}

tree right_rotation(tree t)
{
    tree temp = t->left;
    t->left = temp->right;
    temp->right = t;
    return temp;
}

tree left_right_rotation(tree t)
{
    t->left = left_rotation(t->left);
    return right_rotation(t);
}

tree right_left_rotation(tree t)
{
    t->right = right_rotation(t->right);
    return left_rotation(t);
}

tree insert(int data, tree t)
{
    if (t == NULL)
    {
        t = (tree)malloc(sizeof(struct node));
        t->data = data;
        t->left = NULL;
        t->right = NULL;
    }
    else
    {
        if (data > t->data)
        {
            t->right = insert(data, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (data > t->right->data)
                    t = left_rotation(t);
                else
                    t = right_left_rotation(t);
            }
        }
        else
        {
            t->left = insert(data, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (data < t->left->data)
                    t = right_rotation(t);
                else
                    t = left_right_rotation(t);
            }
        }
    }
    return t;
}

tree delete_node(int data, tree t)
{
    if (t == NULL)
    {
        printf("Element not found\n");
    }
    else
    {
        if (data > t->data)
        {
            t->right = delete_node(data, t->right);
            if (height(t->left) - height(t->right) == 2)
            {
                if (height(t->left->right) > height(t->left->left))
                    t = left_right_rotation(t);
                else
                    t = right_rotation(t);
            }
        }
        else if (data < t->data)
        {
            t->left = delete_node(data, t->left);
            if (height(t->right) - height(t->left) == 2)
            {
                if (height(t->right->left) > height(t->right->right))
                    t = right_left_rotation(t);
                else
                    t = left_rotation(t);
            }
        }
        else
        {
            if (t->left == NULL && t->right == NULL)
            {
                free(t);
                t = NULL;
            }
            else if (t->left == NULL)
            {
                tree temp = t;
                t = t->right;
                free(temp);
            }
            else if (t->right == NULL)
            {
                tree temp = t;
                t = t->left;
                free(temp);
            }
            else
            {
                tree temp = t->right;
                while (temp->left)
                    temp = temp->left;
                t->data = temp->data;
                t->right = delete_node(temp->data, t->right);
            }
        }
    }
    return t;
}
void inorder(tree t)
{
    if (t != NULL)
    {
        inorder(t->left);
        printf("%d ", t->data);
        inorder(t->right);
    }
}

int main()
{
    tree t = create_tree();
    t = insert(1, t);
    t = insert(5, t);
    t = insert(2, t);
    t = insert(3, t);
    t = insert(6, t);
    t = insert(17, t);
    inorder(t);
    printf("\n");
    t = delete_node(5, t);
    t = delete_node(1, t);
    inorder(t);
    return 0;
}