#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class Splay_tree {
public:
    Node* root;

    Splay_tree(int data) {
        root = new Node();
        root->data = data;
        root->left = root->right = nullptr;
    }

    Node* rightRotate(Node* root);
    Node* leftRotate(Node* root);
    Node* Splay(Node* root, int key);
    void insert_node(int data, Node*& root);
    void delete_node(int data, Node*& root);
    bool search_node(int data, Node*& root);
    void print_tree(Node* root);
};

Node* Splay_tree::rightRotate(Node* root) {
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    return tmp;
}

Node* Splay_tree::leftRotate(Node* root) {
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    return tmp;
}

Node* Splay_tree::Splay(Node* root, int key) {
    if (root == nullptr || root->data == key) {
        return root;
    }
    if (root->data > key) {
        if (root->left == nullptr) {
            return root;
        }
        if (root->left->data > key) {
            root->left->left = Splay(root->left->left, key);
            root = rightRotate(root);
        } else if (root->left->data < key) {
            root->left->right = Splay(root->left->right, key);
            if (root->left->right != nullptr) {
                root->left = leftRotate(root->left);
            }
        }
        return (root->left == nullptr) ? root : rightRotate(root);
    } else {
        if (root->right == nullptr) {
            return root;
        }
        if (root->right->data > key) {
            root->right->left = Splay(root->right->left, key);
            if (root->right->left != nullptr) {
                root->right = rightRotate(root->right);
            }
        } else if (root->right->data < key) {
            root->right->right = Splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

void Splay_tree::insert_node(int data, Node*& root) {
    if (root == nullptr) {
        root = new Node();
        root->data = data;
        root->left = root->right = nullptr;
        return;
    }
    root = Splay(root, data);
    if (root->data == data) {
        return;
    }
    Node* new_node = new Node();
    new_node->data = data;
    if (root->data > data) {
        new_node->right = root;
        new_node->left = root->left;
        root->left = nullptr;
    } else {
        new_node->left = root;
        new_node->right = root->right;
        root->right = nullptr;
    }
    root = new_node;
}

void Splay_tree::delete_node(int data, Node*& root) {
    if (root == nullptr) {
        return;
    }
    root = Splay(root, data);
    if (root->data != data) {
        return;
    }
    if (root->left == nullptr) {
        Node* temp = root;
        root = root->right;
        delete temp;
    } else {
        Node* temp = root;
        root = Splay(root->left, data);
        root->right = temp->right;
        delete temp;
    }
}

bool Splay_tree::search_node(int data, Node*& root) {
    root = Splay(root, data);
    return root != nullptr && root->data == data;
}

void Splay_tree::print_tree(Node* root) {
    if (root == nullptr) {
        return;
    }
    print_tree(root->left);
    cout << root->data << " ";
    print_tree(root->right);
}

int main() {
    Splay_tree splay = Splay_tree(100);
    splay.insert_node(10, splay.root);
    splay.insert_node(20, splay.root);
    splay.insert_node(30, splay.root);

    cout << "Tree after insertions: ";
    splay.print_tree(splay.root);
    cout << endl;

    splay.delete_node(20, splay.root);
    cout << "Tree after deletion of 20: ";
    splay.print_tree(splay.root);
    cout << endl;

    bool found = splay.search_node(100, splay.root);
    cout << "Search for 10: " << (found ? "Found" : "Not Found") << endl;
    splay.print_tree(splay.root);

    found = splay.search_node(20, splay.root);
    cout << "Search for 20: " << (found ? "Found" : "Not Found") << endl;

    return 0;
}