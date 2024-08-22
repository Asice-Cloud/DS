#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// 定义B树的阶数
const int ORDER = 4; // B树的阶数

// B树节点结构
template <class T> class BTreeNode {
public:
  bool isLeaf;                          // 是否为叶子节点
  std::vector<T> keys;                  // 节点中的关键字
  std::vector<BTreeNode<T> *> children; // 子节点指针
  int n;                                // 节点中的关键字数

  BTreeNode(bool leaf);
  void traverse();
  BTreeNode<T> *search(T key);
  void insertNonFull(T key);
  void splitChild(int i, BTreeNode<T> *y);
  void remove(T key);
  void removeFromLeaf(int idx);
  void removeFromNonLeaf(int idx);
  T getPredecessor(int idx);
  T getSuccessor(int idx);
  void fill(int idx);
  void borrowFromPrev(int idx);
  void borrowFromNext(int idx);
  void merge(int idx);

  // 为了访问私有成员变量, 需要将BTree声明为友元类,
  // 这样BTree就可以访问BTreeNode的私有成员变量, 从而实现插入和删除操作
  // 为什么不使用继承：因为BTree和BTreeNode是两个不同的类，继承会使得BTree和BTreeNode耦合在一起，不利于代码的维护和扩展
  template <class U> friend class BTree;
};

// B树结构
template <class T> class BTree {
public:
  BTreeNode<T> *root; // 树的根节点
  int order;          // 树的阶数

  BTree() : root(nullptr), order(ORDER) {}
  void traverse() {
    if (root != nullptr)
      root->traverse();
  }
  BTreeNode<T> *search(T key) {
    return (root == nullptr) ? nullptr : root->search(key);
  }
  void insert(T key);
  void remove(T key);
  void visualize_tree(const std::string &filename);
  void generate_dot(BTreeNode<T> *node, std::ofstream &file);
};

// B树节点构造函数
template <class T> BTreeNode<T>::BTreeNode(bool leaf) {
  isLeaf = leaf;
  n = 0;
  keys.resize(2 * ORDER - 1);
  children.resize(2 * ORDER);
}

// 遍历B树
template <class T> void BTreeNode<T>::traverse() {
  int i;
  // 遍历子节点
  for (i = 0; i < n; i++) {
    // 非叶子节点继续遍历
    if (!isLeaf) {
      children[i]->traverse();
    }
    std::cout << " " << keys[i];
  }
  // 遍历最后一个子节点
  if (!isLeaf) {
    children[i]->traverse();
  }
}

// 搜索B树中的一个关键字
template <class T> BTreeNode<T> *BTreeNode<T>::search(T key) {
  int i = 0;
  // 找到第一个大于等于key的关键字
  while (i < n && key > keys[i]) {
    i++;
  }
  if (keys[i] == key) {
    return this;
  }
  // 如果是叶子节点，说明没有找到
  if (isLeaf) {
    return nullptr;
  }
  return children[i]->search(key);
}

// 插入新关键字
template <class T> void BTree<T>::insert(T key) {
  if (root == nullptr) {
    root = new BTreeNode<T>(true);
    root->keys[0] = key;
    root->n = 1;
  } else {
    // 如果根节点满了，需要分裂, 新建一个节点作为根节点
    if (root->n == 2 * ORDER - 1) {
      // 创建一个新节点, 作为根节点, 将原来的根节点作为子节点
      BTreeNode<T> *s = new BTreeNode<T>(false);
      s->children[0] = root;
      s->splitChild(0, root);
      // 选择子节点插入, 保证根节点不满
      int i = 0;
      if (s->keys[0] < key) {
        i++;
      }
      s->children[i]->insertNonFull(key);
      // 更新根节点
      root = s;
    } else {
      root->insertNonFull(key);
    }
  }
}

// 在未满的节点中插入关键字
template <class T> void BTreeNode<T>::insertNonFull(T key) {
  // 找到插入位置
  int i = n - 1;
  // 如果是叶子节点，直接插入
  if (isLeaf) {
    // 找到插入位置, 同时后移关键字, 空出位置
    while (i >= 0 && keys[i] > key) {
      keys[i + 1] = keys[i];
      i--;
    }
    keys[i + 1] = key;
    n++;
  } else {
    while (i >= 0 && keys[i] > key) {
      i--;
    }
    // 如果子节点满了, 先分裂子节点
    if (children[i + 1]->n == 2 * ORDER - 1) {
      splitChild(i + 1, children[i + 1]);
      if (keys[i + 1] < key) {
        i++;
      }
    }
    children[i + 1]->insertNonFull(key);
  }
}

// 分裂子节点
template <class T> void BTreeNode<T>::splitChild(int i, BTreeNode<T> *y) {
  BTreeNode<T> *z = new BTreeNode<T>(y->isLeaf);
  z->n = ORDER - 1;
  for (int j = 0; j < ORDER - 1; j++) {
    z->keys[j] = y->keys[j + ORDER];
  }
  if (!y->isLeaf) {
    // 将y的子节点移到z
    for (int j = 0; j < ORDER; j++) {
      z->children[j] = y->children[j + ORDER];
    }
  }
  // 更新y的关键字数量
  y->n = ORDER - 1;
  // 这里是要将root的子节点后移
  for (int j = n; j >= i + 1; j--) {
    children[j + 1] = children[j];
  }
  // 将z插入到root
  children[i + 1] = z;
  // 将y的中间关键字插入到root
  for (int j = n - 1; j >= i; j--) {
    keys[j + 1] = keys[j];
  }
  // 将y的中间关键字插入到root
  keys[i] = y->keys[ORDER - 1];
  n++;
}

// 删除操作
template <class T> void BTree<T>::remove(T key) {
  if (!root) {
    std::cout << "The tree is empty\n";
    return;
  }
  root->remove(key);
  if (root->n == 0) {
    BTreeNode<T> *tmp = root;
    if (root->isLeaf) {
      root = nullptr;
    } else {
      root = root->children[0];
    }
    delete tmp;
  }
}

// 删除键值
template <class T> void BTreeNode<T>::remove(T key) {
  int idx = 0;
  while (idx < n && keys[idx] < key) {
    idx++;
  }
  if (idx < n && keys[idx] == key) {
    if (isLeaf) {
      removeFromLeaf(idx);
    } else {
      removeFromNonLeaf(idx);
    }
  } else {
    if (isLeaf) {
      std::cout << "The key " << key << " is not present in the tree\n";
      return;
    }
    // 标记是否是最后一个子节点, 用于递归删除,
    // 保证删除后的节点关键字数量不小于ORDER
    bool flag = (idx == n);
    if (children[idx]->n < ORDER) {
      fill(idx);
    }
    // 如果是最后一个子节点, 递归删除
    if (flag && idx > n) {
      children[idx - 1]->remove(key);
    } else {
      children[idx]->remove(key);
    }
  }
}

// 从叶子节点中删除键值
template <class T> void BTreeNode<T>::removeFromLeaf(int idx) {
  for (int i = idx + 1; i < n; ++i) {
    keys[i - 1] = keys[i];
  }
  n--;
}

// 从非叶子节点中删除键值
template <class T> void BTreeNode<T>::removeFromNonLeaf(int idx) {
  T key = keys[idx];
  if (children[idx]->n >= ORDER) {
    T pred = getPredecessor(idx);
    keys[idx] = pred;
    children[idx]->remove(pred);
  } else if (children[idx + 1]->n >= ORDER) {
    T succ = getSuccessor(idx);
    keys[idx] = succ;
    children[idx + 1]->remove(succ);
  } else {
    merge(idx);
    children[idx]->remove(key);
  }
}

// 获取前驱
template <class T> T BTreeNode<T>::getPredecessor(int idx) {
  // 从子节点中找到前驱, 一直找到叶子节点, 即最右边的节点
  BTreeNode<T> *cur = children[idx];
  while (!cur->isLeaf) {
    cur = cur->children[cur->n];
  }
  return cur->keys[cur->n - 1];
}

// 获取后继
template <class T> T BTreeNode<T>::getSuccessor(int idx) {
  // 从子节点中找到后继, 一直找到叶子节点, 即最左边的节点
  BTreeNode<T> *cur = children[idx + 1];
  while (!cur->isLeaf) {
    cur = cur->children[0];
  }
  return cur->keys[0];
}

// 填充节点
template <class T> void BTreeNode<T>::fill(int idx) {
  // 如果前一个子节点有多余的关键字, 从前一个子节点借一个关键字
  if (idx != 0 && children[idx - 1]->n >= ORDER) {
    borrowFromPrev(idx);
  } else if (idx != n && children[idx + 1]->n >= ORDER) {
    // 如果后一个子节点有多余的关键字, 从后一个子节点借一个关键字
    borrowFromNext(idx);
  } else {
    if (idx != n) {
      // 如果后一个子节点有多余的关键字, 合并子节点,
      // 合并后的子节点关键字数量为ORDER-1，然后删除关键字
      merge(idx);
    } else {
      // 最后一个子节点合并前一个子节点
      merge(idx - 1);
    }
  }
}

// 借值的过程类似于旋转，从前一个子节点借一个键值，或者从后一个子节点借一个键值，如果前一个子节点或者后一个子节点有多余的键值，直接借用，否则合并子节点。
//  从前一个子节点借一个键值
/*
         move keys[idx] from parent to children[idx]
                        /       \
   previous provider   /         \ borrow

*/
template <class T> void BTreeNode<T>::borrowFromPrev(int idx) {
  BTreeNode<T> *child = children[idx];
  BTreeNode<T> *sibling = children[idx - 1];
  // 后移关键字
  for (int i = child->n - 1; i >= 0; --i) {
    child->keys[i + 1] = child->keys[i];
  }
  // 如果不是叶子节点, 后移子节点
  if (!child->isLeaf) {
    for (int i = child->n; i >= 0; --i) {
      child->children[i + 1] = child->children[i];
    }
  }
  // 将父节点的关键字下移, 将前一个子节点的最后一个关键字上移, 更新关键字数量
  child->keys[0] = keys[idx - 1];
  if (!child->isLeaf) {
    // 如果不是叶子节点,
    // 将前一个子节点的最后一个子节点移到当前子节点的第一个子节点
    child->children[0] = sibling->children[sibling->n];
  }
  keys[idx - 1] = sibling->keys[sibling->n - 1];
  child->n += 1;
  sibling->n -= 1;
}

/*
    move keys[idx] from parent to children[idx]
            /      \
    borrow /        \ (next)provoder

*/

// 从下一个子节点借一个键值
template <class T> void BTreeNode<T>::borrowFromNext(int idx) {
  BTreeNode<T> *child = children[idx];
  BTreeNode<T> *sibling = children[idx + 1];
  child->keys[(child->n)] = keys[idx];
  if (!(child->isLeaf)) {
    child->children[(child->n) + 1] = sibling->children[0];
  }
  keys[idx] = sibling->keys[0];
  for (int i = 1; i < sibling->n; ++i) {
    sibling->keys[i - 1] = sibling->keys[i];
  }
  if (!sibling->isLeaf) {
    for (int i = 1; i <= sibling->n; ++i) {
      sibling->children[i - 1] = sibling->children[i];
    }
  }
  child->n += 1;
  sibling->n -= 1;
}

// 合并子节点
template <class T> void BTreeNode<T>::merge(int idx) {
  BTreeNode<T> *child = children[idx];
  BTreeNode<T> *sibling = children[idx + 1];
  // 将父节点的关键字下移
  child->keys[ORDER - 1] = keys[idx];
  // 将sibling的关键字移到child
  for (int i = 0; i < sibling->n; ++i) {
    child->keys[i + ORDER] = sibling->keys[i];
  }
  if (!child->isLeaf) {
    for (int i = 0; i <= sibling->n; ++i) {
      child->children[i + ORDER] = sibling->children[i];
    }
  }
  // 更新父节点的关键字
  for (int i = idx + 1; i < n; ++i) {
    keys[i - 1] = keys[i];
  }
  // 更新父节点的子节点
  for (int i = idx + 2; i <= n; ++i) {
    children[i - 1] = children[i];
  }
  child->n += sibling->n + 1;
  n--;
  delete sibling;
}

// 生成DOT文件
template <class T> void BTree<T>::visualize_tree(const std::string &filename) {
  std::ofstream file;
  file.open(filename);
  file << "digraph BTree {" << std::endl;
  file << "node [shape=record];" << std::endl;
  if (root != nullptr) {
    generate_dot(root, file);
  }
  file << "}" << std::endl;
  file.close();
}

// 递归生成DOT文件内容
template <class T>
void BTree<T>::generate_dot(BTreeNode<T> *node, std::ofstream &file) {
  static int nullCount = 0;
  file << "node" << node << " [label=\"";
  for (int i = 0; i < node->n; i++) {
    file << "<f" << i << "> " << node->keys[i];
    if (i != node->n - 1)
      file << "|";
  }
  file << "\"];" << std::endl;
  if (!node->isLeaf) {
    for (int i = 0; i <= node->n; i++) {
      if (node->children[i] != nullptr) {
        file << "node" << node << ":f" << i << " -> node" << node->children[i]
             << ";" << std::endl;
        generate_dot(node->children[i], file);
      } else {
        file << "null" << nullCount << " [shape=point];" << std::endl;
        file << "node" << node << ":f" << i << " -> null" << nullCount << ";"
             << std::endl;
        nullCount++;
      }
    }
  }
}

// 测试函数
void testBTree() {
  BTree<int> t;
  srand(time(0));
  for (int i = 0; i < 63; i++) {
    int num = rand() % 100; // 生成0到999之间的随机数
    t.insert(num);
  }
  std::cout << "Traversal of the constructed B-tree is:\n";
  t.traverse();
  t.visualize_tree("btree.dot");
  std::cout << std::endl;
}

// 测试B树
int main() {
  testBTree();
  BTree<int> t;
  t.insert(10);
  t.insert(20);
  t.insert(5);
  t.remove(5);
  t.traverse();

  return 0;
}
