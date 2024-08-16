#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node *child;
    Node *sibling;
    Node(int data) : data(data), child(NULL), sibling(NULL)
    {
    }
};

class BinomialQueue
{
  public:
    Node *head;
    BinomialQueue()
    {
        head = NULL;
    }
    void insert(int data)
    {
        BinomialQueue *queue = new BinomialQueue();
        queue->head = create_node(data);
        merge(this, queue);
    }
    int extract_min()
    {
        Node *prev = NULL;
        Node *min = head;
        Node *min_prev = NULL;
        Node *node = head;
        while (node->sibling != NULL)
        {
            if (node->sibling->data < min->data)
            {
                min = node->sibling;
                min_prev = prev;
            }
            prev = node;
            node = node->sibling;
        }
        if (min_prev == NULL)
        {
            head = min->sibling;
        }
        else
        {
            min_prev->sibling = min->sibling;
        }
        BinomialQueue *queue = new BinomialQueue();
        queue->head = min->child;
        reverse(queue);
        merge(this, queue);
        return min->data;
    }
    void reverse(BinomialQueue *queue)
    {
        Node *prev = NULL;
        Node *node = queue->head;
        while (node != NULL)
        {
            Node *next = node->sibling;
            node->sibling = prev;
            prev = node;
            node = next;
        }
        queue->head = prev;
    }
    void merge(BinomialQueue *queue1, BinomialQueue *queue2)
    {
        Node *node1 = queue1->head;
        Node *node2 = queue2->head;
        Node *head = NULL;
        Node *tail = NULL;
        while (node1 != NULL && node2 != NULL)
        {
            Node *node = NULL;
            if (node1->data < node2->data)
            {
                node = node1;
                node1 = node1->sibling;
            }
            else
            {
                node = node2;
                node2 = node2->sibling;
            }
            if (head == NULL)
            {
                head = node;
                tail = node;
            }
            else
            {
                tail->sibling = node;
                tail = node;
            }
        }
        while (node1 != NULL)
        {
            if (head == NULL)
            {
                head = node1;
                tail = node1;
            }
            else
            {
                tail->sibling = node1;
                tail = node1;
            }
            node1 = node1->sibling;
        }
        while (node2 != NULL)
        {
            if (head == NULL)
            {
                head = node2;
                tail = node2;
            }
            else
            {
                tail->sibling = node2;
                tail = node2;
            }
            node2 = node2->sibling;
        }
        queue1->head = head;
    }
    Node *create_node(int data)
    {
        return new Node(data);
    }
    void print()
    {
        Node *node = head;
        while (node != NULL)
        {
            cout << node->data << " ";
            node = node->sibling;
        }
        cout << endl;
    }
};

int main()
{
    BinomialQueue *queue = new BinomialQueue();
    for (int i = 1; i < 20; i++)
    {
        queue->insert(i);
    }
    queue->print();
    queue->extract_min();
    queue->print();
}