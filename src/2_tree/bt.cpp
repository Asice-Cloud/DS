#include<iostream>
#include<string>

template <class T>
struct node
{
    T data;
    node<T> *left;
    node<T> *right;
};

template<class T>
class Tree{
    public:
        Tree();
        ~Tree();
        void insert(T data);
        void remove(T data);
        std::pair<T, node<T>*> search(T data);
        void print_tree(node<T>* t);
        node<T>* get_root(){return root;}
    private:
        node<T> *root;
        void delete_tree(node<T> *t);
};

template<class T>
Tree<T>::Tree():root(nullptr){}

template<class T>
Tree<T>::~Tree(){
    delete_tree(root);
}

template<class T>
void Tree<T>::delete_tree(node<T> *t){
    if(t==nullptr)
        return;
    delete_tree(t->left);
    delete_tree(t->right);
    delete t;
}

/*
template<class T>
void Tree<T>::insert(T data){
    node<T> *t = new node<T>;
    node<T> *parent = nullptr;
    t->data = data;
    t->left = nullptr;
    t->right = nullptr;
    if(root==nullptr)
        root = t;
    else{
        node<T> *curr;
        curr = root;
        while(curr){
            parent = curr;
            if(t->data > curr->data)
                curr = curr->right;
            else
                curr = curr->left;
        }
        if(t->data < parent->data)
            parent->left = t;
        else
            parent->right = t;
    }
}
*/

// 第二种新的实现
/*
template<class T>
void Tree<T>::insert(T data){
    node<T>*node_zero = new node<T>;
    node_zero->data = data;

    node<T>*curr = root;
    node<T>**parent = &root;
    while(curr){
        if(data<curr->data){
            parent = &curr->left;
            curr = curr->left;
            continue;
        }else{
            parent = &curr->right;
            curr = curr->right;
            continue;
        }
    }
    if(parent==nullptr){
        root = node_zero;
    }else{
        *parent = node_zero;
    }
}
*/

// 第三种新的实现
template<class T>
void Tree<T>::insert(T data){
    node<T>*node_zero = new node<T>;
    node_zero->data = data;

    node<T>**next = &root;
    while(*next){
        if(data<(*next)->data){
            next = &(*next)->left;
            continue;
        }else{
            next = &(*next)->right;
            continue;
        }
    }
    if(next==nullptr){
        root = node_zero;
    }else{
        *next = node_zero;
    }
}

template<class T>
std::pair<T, node<T>*> Tree<T>::search(T data){
    node<T> *curr = root;
    while(curr){
        if(curr->data == data)
            return std::make_pair(curr->data, curr);
        else if(data > curr->data)
            curr = curr->right;
        else
            curr = curr->left;
    }
    return std::make_pair(T(), nullptr);
}

template<class T>
void Tree<T>::remove(T value) {
    node<T>** pos = &root;
    while (*pos && (*pos)->data != value) {
        if (value < (*pos)->data)
            pos = &(*pos)->left;
        else
            pos = &(*pos)->right;
    }
    if (*pos == nullptr) return; // 没有找到要删除的节点

    if ((*pos)->left == nullptr) {
        node<T>* temp = *pos;
        *pos = (*pos)->right;
        delete temp;
    } else if ((*pos)->right == nullptr) {
        node<T>* temp = *pos;
        *pos = (*pos)->left;
        delete temp;
    } else {
        node<T>* temp = (*pos)->right;
        while (temp->left)
            temp = temp->left;
        (*pos)->data = temp->data;
        remove(temp->data); // 递归删除
    }
}

template<class T>
void Tree<T>::print_tree(node<T>* t) {
    if (t == nullptr)
        return;
    std::cout << t->data << " ";
    print_tree(t->left);
    print_tree(t->right);
}

int main(){
    Tree<int> t;
    t.insert(1);
    t.insert(5);
    t.insert(2);
    t.insert(6);
    t.insert(17);
    t.insert(3);
    t.insert(4);
    
    t.print_tree(t.get_root());
    std::cout<<'\n';
    t.remove(3);
    t.print_tree(t.get_root());
    return 0;
}