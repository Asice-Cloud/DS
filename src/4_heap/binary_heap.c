#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct binary_heap
{
    int *array;
    int capacity;
    int size;
};

typedef struct binary_heap *PriorityQueue;

PriorityQueue init(int MaxElements)
{
    PriorityQueue H;
    H = (PriorityQueue)malloc(sizeof(struct binary_heap));
    if (H == NULL)
    {
        printf("Out of space\n");
        return NULL;
    }
    H->array = (int *)malloc(sizeof(int) * (MaxElements + 1));
    if (H->array == NULL)
    {
        printf("Out of space\n");
        return NULL;
    }
    H->capacity = MaxElements;
    H->size = 0;
    H->array[0] = -1;
    return H;
}

bool isEmpty(PriorityQueue H)
{
    return H->size == 0;
}

bool isFull(PriorityQueue H)
{
    return H->size == H->capacity;
}

void insert(int x, PriorityQueue H)
{
    int i;
    if (isFull(H))
    {
        printf("Priority queue is full\n");
        return;
    }
    for (i = ++H->size; H->array[i / 2] > x; i /= 2)
        H->array[i] = H->array[i / 2];
    H->array[i] = x;
}

int delete_min(PriorityQueue H)
{
    int i, child;
    int minElement, lastElement;

    if (isEmpty(H))
    {
        printf("Priority queue is empty\n");
        return H->array[0];
    }

    minElement = H->array[1];
    lastElement = H->array[H->size--];

    for (i = 1; i * 2 <= H->size; i = child)
    {
        child = i * 2;
        if (child != H->size && H->array[child + 1] < H->array[child])
        {
            child++;
        }
        if (lastElement > H->array[child])
        {
            H->array[i] = H->array[child];
        }
        else
        {
            break;
        }
    }
    H->array[i] = lastElement;
    return minElement;
}

void destroy(PriorityQueue H)
{
    free(H->array);
    free(H);
}

int find_min(PriorityQueue H)
{
    if (isEmpty(H))
    {
        printf("Priority queue is empty\n");
        return H->array[0];
    }
    return H->array[1];
}

int main()
{
    PriorityQueue H = init(10);
    insert(3, H);
    insert(2, H);
    insert(10, H);
    insert(4, H);
    insert(5, H);
    insert(6, H);
    insert(7, H);
    insert(8, H);
    insert(9, H);
    insert(10, H);
    insert(11, H);
    printf("Min element: %d\n", find_min(H));
    printf("Delete min element: %d\n", delete_min(H));
    printf("Min element: %d\n", find_min(H));
    destroy(H);
    return 0;
}