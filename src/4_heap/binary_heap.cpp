#include<iostream>
#include<vector>
using namespace std;

struct binary_heap
{
    vector<int> array;
    int capacity;
    int size;
};

class PriorityQueue
{
public:
    binary_heap *H;
    PriorityQueue(int MaxElements)
    {
        H = new binary_heap;
        H->array.resize(MaxElements + 1);
        H->capacity = MaxElements;
        H->size = 0;
        H->array[0] = -1;
    }

    bool isEmpty()
    {
        return H->size == 0;
    }

    bool isFull()
    {
        return H->size == H->capacity;
    }

    void insert(int x)
    {
        int i;
        if (isFull())
        {
            cout << "Priority queue is full\n";
            return;
        }
        for (i = ++H->size; H->array[i / 2] > x; i /= 2)
            H->array[i] = H->array[i / 2];
        H->array[i] = x;
    }

    int delete_min()
    {
        int i, child;
        int min, last;
        if (isEmpty())
        {
            cout << "Priority queue is empty\n";
            return -1;
        }
        min = H->array[1];
        last = H->array[H->size--];
        for (i = 1; i * 2 <= H->size; i = child)
        {
            child = i * 2;
            if (child != H->size && H->array[child + 1] < H->array[child])
                child++;
            if (last > H->array[child])
                H->array[i] = H->array[child];
            else
                break;
        }
        H->array[i] = last;
        return min;
    }

    ~PriorityQueue()
    {
        delete H;
    }

    void print()
    {
        for (int i = 1; i <= H->size; i++)
            cout << H->array[i] << " ";
        cout << endl;
    }
};

int main()
{
    PriorityQueue pq(10);
    pq.insert(50);
    pq.insert(60);
    pq.insert(10);
    pq.insert(20);
    pq.insert(30);
    pq.insert(40);
    pq.insert(100);
    pq.insert(110);
    pq.insert(70);
    pq.insert(80);
    pq.insert(90);
    pq.print();
    cout << pq.delete_min() << endl;
    cout << pq.delete_min() << endl;
    pq.print();

    return 0;
}