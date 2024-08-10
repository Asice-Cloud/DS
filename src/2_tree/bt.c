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
      t->right = insert(data, t->right);
    else
      t->left = insert(data, t->left);
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
    }
    else if (data < t->data)
    {
      t->left = delete_node(data, t->left);
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
        while (temp->left != NULL)
        {
          temp = temp->left;
        }
        t->data = temp->data;
        t->right = delete_node(temp->data, t->right);
      }
    }
  }
  return t;
}

void print_tree(tree t)
{
  if (t == NULL)
    return;
  print_tree(t->left);
  printf("%d ", t->data);
  print_tree(t->right);
}

int main()
{
  tree t1 = create_tree();
  t1 = insert(1, t1);
  t1 = insert(2, t1);
  t1 = insert(5, t1);
  t1 = insert(3, t1);
  t1 = insert(8, t1);
  t1 = insert(6, t1);
  print_tree(t1);
  printf("\n");
  t1 = delete_node(5, t1);
  print_tree(t1);
  printf("\n");
  return 0;
}