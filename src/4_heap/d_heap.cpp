#include<iostream>
#include<vector>

using namespace std;

struct d_heap
{
    vector<int> array;
    int capacity;
    int size;
    int d;
};

class PriorityQueue
{
public:
    d_heap *H;
    PriorityQueue(int MaxElements, int d)
    {
        H = new d_heap;
        H->array.resize(MaxElements + 1);
        H->capacity = MaxElements;
        H->size = 0;
        H->array[0] = -1;
        H->d = d;
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
        // 这里i+H->d-2是为了找到当前节点的父节点，然后再除以H->d，找到当前节点的父节点的父节点
        for (i = ++H->size; H->array[(i + H->d - 2) / H->d] > x; i = (i + H->d - 2) / H->d)
            H->array[i] = H->array[(i + H->d - 2) / H->d];
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
        for (i = 1; i * H->d <= H->size; i = child)
        {
            child = find_min_child(i);
            if (last > H->array[child])
                H->array[i] = H->array[child];
            else
                break;
        }
        H->array[i] = last;
        return min;
    }

    int find_min_child(int i)
    {
        int k = i * H->d + 1;
        int min_child = k;
        for (int j = 2; j <= H->d; j++)
        {
            if (k + j <= H->size && H->array[k + j] < H->array[min_child])
                min_child = k + j;
        }
        return min_child;
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
    PriorityQueue pq(10, 3);
    pq.insert(3);
    pq.insert(2);
    pq.insert(15);
    pq.insert(5);
    pq.insert(4);
    pq.insert(45);
    pq.print();
    cout << pq.delete_min() << endl;
    cout << pq.delete_min() << endl;
    pq.print();
    return 0;
}