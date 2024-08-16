#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct node
{
    int data;
    struct node *child;
    struct node *sibling;
} Node;

typedef struct binomial_queue
{
    Node *head;
} BinomialQueue;

BinomialQueue *create_binomial_queue()
{
    BinomialQueue *queue = (BinomialQueue *)malloc(sizeof(BinomialQueue));
    queue->head = NULL;
    return queue;
}

Node *create_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

void merge(BinomialQueue *queue1, BinomialQueue *queue2)
{
    Node *head1 = queue1->head;
    Node *head2 = queue2->head;
    Node *head = NULL;
    Node *tail = NULL;
    Node *node1 = head1;
    Node *node2 = head2;
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

void insert(BinomialQueue *queue, int data)
{
    Node *node = create_node(data);
    BinomialQueue *new_queue = create_binomial_queue();
    new_queue->head = node;
    merge(queue, new_queue);
}

int delete_min(BinomialQueue *queue)
{
    Node *head = queue->head;
    Node *prev = NULL;
    Node *prev_min = NULL;
    Node *min = NULL;
    Node *node = head;
    Node *prev_node = NULL;
    while (node != NULL)
    {
        if (min == NULL || node->data < min->data)
        {
            min = node;
            prev_min = prev_node;
        }
        prev_node = node;
        prev = node;
        node = node->sibling;
    }
    if (prev_min == NULL)
    {
        queue->head = min->sibling;
    }
    else
    {
        prev_min->sibling = min->sibling;
    }
    int data = min->data;
    free(min);
    return data;
}

void print(BinomialQueue *queue)
{
    Node *head = queue->head;
    Node *node = head;
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->sibling;
    }
    printf("\n");
}

int main()
{
    BinomialQueue *queue = create_binomial_queue();
    insert(queue, 1);
    insert(queue, 2);
    insert(queue, 3);
    insert(queue, 4);
    insert(queue, 5);
    insert(queue, 6);
    insert(queue, 7);
    insert(queue, 8);
    insert(queue, 9);
    insert(queue, 10);
    print(queue);
    printf("%d\n", delete_min(queue));
    printf("%d\n", delete_min(queue));
    print(queue);
    return 0;
}