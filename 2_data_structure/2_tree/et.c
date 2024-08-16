#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// 定义树节点结构
typedef struct TreeNode
{
    char data[MAX];
    struct TreeNode *left, *right;
} TreeNode;

// 创建新节点
TreeNode *create_node(char *data)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(node->data, data);
    node->left = node->right = NULL;
    return node;
}

// 计算表达式树的值
int evaluate_tree(TreeNode *root)
{
    if (root == NULL)
        return 0;

    // 如果是叶子节点，返回其值
    if (!root->left && !root->right)
        return atoi(root->data);

    // 递归计算左子树和右子树的值
    int left_val = evaluate_tree(root->left);
    int right_val = evaluate_tree(root->right);

    // 根据运算符计算结果
    switch (root->data[0])
    {
    case '+':
        return left_val + right_val;
    case '-':
        return left_val - right_val;
    case '*':
        return left_val * right_val;
    case '/':
        return left_val / right_val;
    }
    return 0;
}

// 判断是否为运算符
int is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 获取运算符优先级
int precedence(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return 0;
}

// 中缀表达式转换为后缀表达式
void infix_to_postfix(char *infix, char *postfix)
{
    char stack[MAX][MAX];
    int top = -1;
    int k = 0;

    for (int i = 0; infix[i]; i++)
    {
        if (isdigit(infix[i]))
        {
            while (isdigit(infix[i]))
            {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            i--;
        }
        else if (infix[i] == '(')
        {
            strcpy(stack[++top], "(");
        }
        else if (infix[i] == ')')
        {
            while (top != -1 && strcmp(stack[top], "(") != 0)
            {
                postfix[k++] = stack[top--][0];
                postfix[k++] = ' ';
            }
            top--; // pop '('
        }
        else if (is_operator(infix[i]))
        {
            while (top != -1 && precedence(stack[top][0]) >= precedence(infix[i]))
            {
                postfix[k++] = stack[top--][0];
                postfix[k++] = ' ';
            }
            char op[2] = {infix[i], '\0'};
            strcpy(stack[++top], op);
        }
    }

    while (top != -1)
    {
        postfix[k++] = stack[top--][0];
        postfix[k++] = ' ';
    }

    postfix[k] = '\0';
}

// 使用后缀表达式构建表达式树
TreeNode *construct_tree(char *postfix)
{
    TreeNode *stack[MAX];
    int top = -1;
    char token[MAX];
    int i = 0;

    while (sscanf(postfix + i, "%s", token) == 1)
    {
        i += strlen(token) + 1;
        if (isdigit(token[0]))
        {
            stack[++top] = create_node(token);
        }
        else if (is_operator(token[0]))
        {
            TreeNode *node = create_node(token);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }

    return stack[top];
}

void free_tree(TreeNode *root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main()
{
    char infix[MAX], postfix[MAX];

    // 从控制台读取输入的表达式
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // 将中缀表达式转换为后缀表达式
    infix_to_postfix(infix, postfix);

    // 使用后缀表达式构建表达式树
    TreeNode *root = construct_tree(postfix);

    // 计算表达式树的值
    int result = evaluate_tree(root);
    printf("Expression tree result: %d\n", result);

    // 释放内存
    // 这里省略了释放内存的代码，可以根据需要添加
    free_tree(root);
    return 0;
}