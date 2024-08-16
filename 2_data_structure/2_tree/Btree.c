#include <stdio.h>
#include <stdlib.h>

#define T 4 // B树的最小度数

// B树节点结构
struct BTreeNode
{
    int *keys;            // 关键字数组
    int t;                // 最小度数
    struct BTreeNode **C; // 子节点指针数组
    int n;                // 当前关键字数量
    int leaf;             // 是否为叶节点
};

typedef struct BTreeNode *BTree;

// 创建新节点
BTree create_node(int t, int leaf)
{
    BTree new_node = (BTree)malloc(sizeof(struct BTreeNode));
    new_node->t = t;
    new_node->leaf = leaf;
    new_node->keys = (int *)malloc((2 * t - 1) * sizeof(int));
    new_node->C = (BTree *)malloc(2 * t * sizeof(BTree));
    new_node->n = 0;
    return new_node;
}

// 遍历B树
void traverse(BTree root)
{
    int i;
    // 遍历子节点
    for (i = 0; i < root->n; i++)
    {
        if (!root->leaf)
        {
            traverse(root->C[i]);
        }
        printf("%d ", root->keys[i]);
    }
    // 遍历最后一个子节点
    if (!root->leaf)
    {
        traverse(root->C[i]);
    }
}

// 分裂子节点
void split_child(BTree root, int i, BTree y)
{
    int t = y->t;
    BTree z = create_node(t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
    {
        z->keys[j] = y->keys[j + t];
    }
    if (!y->leaf)
    {
        // 将y的子节点移到z
        for (int j = 0; j < t; j++)
        {
            z->C[j] = y->C[j + t];
        }
    }
    // 更新y的关键字数量
    y->n = t - 1;
    // 这里后移root的关键字和子节点，然后插入z
    for (int j = root->n; j >= i + 1; j--)
    {
        root->C[j + 1] = root->C[j];
    }
    // 将z插入到root
    root->C[i + 1] = z;
    for (int j = root->n - 1; j >= i; j--)
    {
        root->keys[j + 1] = root->keys[j];
    }
    // 将y的中间关键字插入到root
    root->keys[i] = y->keys[t - 1];
    root->n++;
}

// 插入非满节点
void insert_non_full(BTree root, int k)
{
    int i = root->n - 1;
    // 如果是叶节点, 直接插入
    if (root->leaf)
    {
        // 找到插入位置, 并将大于k的关键字后移, 然后插入k
        while (i >= 0 && root->keys[i] > k)
        {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = k;
        root->n++;
    }
    else
    {
        // 找到插入位置, 并将大于k的关键字后移
        while (i >= 0 && root->keys[i] > k)
        {
            i--;
        }
        // 如果子节点满了, 先分裂子节点
        if (root->C[i + 1]->n == 2 * root->t - 1)
        {
            split_child(root, i + 1, root->C[i + 1]);
            if (root->keys[i + 1] < k)
            {
                i++;
            }
        }
        insert_non_full(root->C[i + 1], k);
    }
}

// 插入节点
// 传入类型为BTree*的指针, 用于更新根节点
// 如果传入BTree类型，这是值传递，无法更新根节点
void insert(BTree *root, int k)
{
    if (*root == NULL)
    {
        *root = create_node(T, 1);
        (*root)->keys[0] = k;
        (*root)->n = 1;
    }
    else
    {
        // 如果根节点满了, 先分裂根节点
        if ((*root)->n == 2 * T - 1)
        {
            // 创建新根节点, 并将原根节点作为子节点
            BTree s = create_node(T, 0);
            s->C[0] = *root;
            split_child(s, 0, *root);
            // 选择子节点插入, 保证根节点不满
            int i = 0;
            if (s->keys[0] < k)
            {
                i++;
            }
            insert_non_full(s->C[i], k);
            // 更新根节点
            *root = s;
        }
        else
        {
            insert_non_full(*root, k);
        }
    }
}

int main()
{
    BTree root = NULL;
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);
    insert(&root, 15);
    insert(&root, 16);
    insert(&root, 19);
    insert(&root, 13);
    insert(&root, 14);

    printf("Traversal of the constructed B-tree is:\n");
    traverse(root);
    printf("\n");

    return 0;
}