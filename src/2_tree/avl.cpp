#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

template<class T>
struct node
{
    T data;
    node<T> *left;
    node<T> *right;
    int height;
};

template<class T>
class avl
{
    public: 
        node<T> *root;
        avl() : root(NULL) {}
        int height(node<T> *t);
        int update_height(node<T> *t);
        node<T> *left_rotation(node<T> *t);
        node<T> *right_rotation(node<T> *t);
        node<T> *left_right_rotation(node<T> *t);
        node<T> *right_left_rotation(node<T> *t);
        node<T> *insert(T x, node<T> *t);
        node<T> *find_min(node<T> *t);
        node<T> *find_max(node<T> *t);
        node<T> *remove(T x, node<T> *t);
        void inorder(node<T> *t);
        void preorder(node<T> *t);
        void postorder(node<T> *t);
        void make_empty(node<T> *t);
        node<T> *clone(node<T> *t);
        void print_tree(node<T> *t, int space);
        void generate_dot(node<T> *t, ofstream &file);
        void visualize_tree(const string &filename);
};

template<class T>
int avl<T>::height(node<T> *t)
{
    return t == NULL ? -1 : t->height;
}

template<class T>
int avl<T>::update_height(node<T> *t)
{
    return max(height(t->left), height(t->right)) + 1;
}

template<class T>
node<T> *avl<T>::left_rotation(node<T> *t)
{
    node<T>* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t->height = update_height(t);
    temp->height = update_height(temp);
    return temp;
}

template<class T>
node<T> *avl<T>::right_rotation(node<T> *t)
{
    node<T>* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = update_height(t);
    temp->height = update_height(temp);
    return temp;
}

template<class T>
node<T> *avl<T>::left_right_rotation(node<T> *t)
{
    t->left = left_rotation(t->left);
    return right_rotation(t);
}

template<class T>
node<T> *avl<T>::right_left_rotation(node<T> *t)
{
    t->right = right_rotation(t->right);
    return left_rotation(t);
}

template<class T>
node<T> *avl<T>::insert(T x, node<T> *t)
{
    if (t == NULL)
    {
        t = new node<T>;
        t->data = x;
        t->height = 0;
        t->left = t->right = NULL;
    }
    else if (x < t->data)
    {
        t->left = insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
        {
            if (x < t->left->data)
                t = right_rotation(t);
            else
                t = left_right_rotation(t);
        }
    }
    else if (x > t->data)
    {
        t->right = insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if (x > t->right->data)
                t = left_rotation(t);
            else
                t = right_left_rotation(t);
        }
    }
    t->height = update_height(t);
    return t;
}

template<class T>
node<T> *avl<T>::find_min(node<T> *t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return find_min(t->left);
}

template<class T>
node<T> *avl<T>::find_max(node<T> *t)
{
    if (t == NULL)
        return NULL;
    else if (t->right == NULL)
        return t;
    else
        return find_max(t->right);
}

template<class T>
node<T> *avl<T>::remove(T x, node<T> *t)
{
    node<T> *temp;
    if (t == NULL)
        return NULL;
    else if (x < t->data)
        t->left = remove(x, t->left);
    else if (x > t->data)
        t->right = remove(x, t->right);
    else if (t->left && t->right)
    {
        temp = find_min(t->right);
        t->data = temp->data;
        t->right = remove(t->data, t->right);
    }
    else
    {
        temp = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        delete temp;
    }
    if (t == NULL)
        return t;
    t->height = update_height(t);
    if (height(t->left) - height(t->right) == 2)
    {
        if (height(t->left->left) - height(t->left->right) == 1)
            return right_rotation(t);
        else
            return left_right_rotation(t);
    }
    else if (height(t->right) - height(t->left) == 2)
    {
        if (height(t->right->right) - height(t->right->left) == 1)
            return left_rotation(t);
        else
            return right_left_rotation(t);
    }
    return t;
}

template<class T>
void avl<T>::inorder(node<T> *t)
{
    if (t != NULL)
    {
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
}

template<class T>
void avl<T>::preorder(node<T> *t)
{
    if (t != NULL)
    {
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }
}

template<class T>
void avl<T>::postorder(node<T> *t)
{
    if (t != NULL)
    {
        postorder(t->left);
        postorder(t->right);
        cout << t->data << " ";
    }
}

template<class T>
void avl<T>::make_empty(node<T> *t)
{
    if (t != NULL)
    {
        make_empty(t->left);
        make_empty(t->right);
        delete t;
    }
    t = NULL;
}

template<class T>
node<T> *avl<T>::clone(node<T> *t)
{
    if (t == NULL)
        return NULL;
    else
    {
        node<T> *temp = new node<T>;
        temp->data = t->data;
        temp->left = clone(t->left);
        temp->right = clone(t->right);
        return temp;
    }
}

// 打印树的塔状结构
template<class T>
void avl<T>::print_tree(node<T> *t, int space)
{
    if (t == NULL)
        return;

    // 增加间隔
    space += 10;

    // 打印右子树
    print_tree(t->right, space);

    // 打印当前节点
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << t->data << "\n";

    // 打印左子树
    print_tree(t->left, space);
}

// 生成Graphviz DOT文件
template<class T>
void avl<T>::generate_dot(node<T> *t, ofstream &file)
{
    if (t != NULL)
    {
        if (t->left != NULL)
        {
            file << t->data << " -> " << t->left->data << ";" << endl;
            generate_dot(t->left, file);
        }
        if (t->right != NULL)
        {
            file << t->data << " -> " << t->right->data << ";" << endl;
            generate_dot(t->right, file);
        }
    }
}

// 可视化树
template<class T>
void avl<T>::visualize_tree(const string &filename)
{
    ofstream file;
    file.open(filename);
    file << "digraph AVLTree {" << endl;
    generate_dot(root, file);
    file << "}" << endl;
    file.close();
}

int main()
{
    avl<int> tree;
    srand(time(0));

    // 生成63个随机数并插入到AVL树中
    for (int i = 0; i < 63; ++i)
    {
        int num = rand() % 100; // 生成0到99之间的随机数
        tree.root = tree.insert(num, tree.root);
    }

    // 打印AVL树的中序遍历结果
    cout << "Inorder traversal of the AVL tree:" << endl;
    tree.inorder(tree.root);
    cout << endl;

    // 打印AVL树的塔状结构
    cout << "Tower structure of the AVL tree:" << endl;
    tree.print_tree(tree.root, 0);

    // 生成并可视化AVL树
    string filename = "avl_tree.dot";
    tree.visualize_tree(filename);
    cout << "Graphviz DOT file generated: " << filename << endl;
    cout << "Run the following command to generate the tree image:" << endl;
    cout << "dot -Tpng " << filename << " -o avl_tree.png" << endl;

    return 0;
}