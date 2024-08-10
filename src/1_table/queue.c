#include <stdio.h>
#include <stdlib.h>

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    int *Array;
};

typedef struct QueueRecord *Queue;

int isEmpty(Queue Q)
{
    return Q->Size == 0;
}

int isFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

void MakeEmpty(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

Queue CreateQueue(int MaxElements)
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QueueRecord));
    if (Q == NULL)
    {
        printf("Out of space\n");
        exit(1);
    }
    Q->Array = (int *)malloc(sizeof(int) * MaxElements);
    if (Q->Array == NULL)
    {
        printf("Out of space\n");
        exit(1);
    }
    Q->Capacity = MaxElements;
    MakeEmpty(Q);
    return Q;
}

void DisposeQueue(Queue Q)
{
    if (Q != NULL)
    {
        free(Q->Array);
        free(Q);
    }
}

void Enqueue(int x, Queue Q)
{
    if (isFull(Q))
    {
        printf("Full queue\n");
    }
    else
    {
        Q->Size++;
        Q->Rear = (Q->Rear + 1) % Q->Capacity;
        Q->Array[Q->Rear] = x;
    }
}

int Front(Queue Q)
{
    if (!isEmpty(Q))
    {
        return Q->Array[Q->Front];
    }
    printf("Empty queue\n");
    return 0;
}

void Dequeue(Queue Q)
{
    if (isEmpty(Q))
    {
        printf("Empty queue\n");
    }
    else
    {
        Q->Size--;
        Q->Front = (Q->Front + 1) % Q->Capacity;
    }
}

int FrontAndDequeue(Queue Q)
{
    int x;
    if (isEmpty(Q))
    {
        printf("Empty queue\n");
        return 0;
    }
    else
    {
        Q->Size--;
        x = Q->Array[Q->Front];
        Q->Front = (Q->Front + 1) % Q->Capacity;
        return x;
    }
}

int main()
{
    Queue Q;
    Q = CreateQueue(10);
    Enqueue(1, Q);
    Enqueue(2, Q);
    Enqueue(3, Q);
    Enqueue(4, Q);
    Enqueue(5, Q);
    printf("Front: %d\n", Front(Q));
    Dequeue(Q);
    printf("Front: %d\n", Front(Q));
    Dequeue(Q);
    printf("Front: %d\n", Front(Q));

    DisposeQueue(Q);
    printf("Front: %d\n", Front(Q));

    return 0;
}