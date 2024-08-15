#include <iostream>
#include <utility> // for std::pair
#include <vector>
using namespace std;

class binary_heap
{
  public:
    vector<pair<int, int>> array; // 使用pair来存储优先级和数据
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
        H->array[0] = make_pair(-1, -1); // 哨兵元素
    }

    bool isEmpty()
    {
        return H->size == 0;
    }

    bool isFull()
    {
        return H->size == H->capacity;
    }

    void insert(int priority, int value)
    {
        int i;
        if (isFull())
        {
            cout << "Priority queue is full\n";
            return;
        }

        // Percolate up
        for (i = ++H->size; H->array[i / 2].first > priority; i /= 2)
        {
            H->array[i] = H->array[i / 2];
        }
        H->array[i] = make_pair(priority, value);
    }

    pair<int, int> deleteMin()
    {
        if (isEmpty())
        {
            cout << "Priority queue is empty\n";
            return make_pair(-1, -1);
        }

        pair<int, int> minElement = H->array[1];
        pair<int, int> lastElement = H->array[H->size--];

        int i, child;
        for (i = 1; i * 2 <= H->size; i = child)
        {
            child = i * 2;
            if (child != H->size && H->array[child + 1].first < H->array[child].first)
                child++;
            if (lastElement.first > H->array[child].first)
                H->array[i] = H->array[child];
            else
                break;
        }
        H->array[i] = lastElement;

        return minElement;
    }
};

int main()
{
    PriorityQueue pq(10);
    pq.insert(3, 100);
    pq.insert(1, 200);
    pq.insert(2, 300);

    while (!pq.isEmpty())
    {
        pair<int, int> minElement = pq.deleteMin();
        cout << "Priority: " << minElement.first << ", Value: " << minElement.second << endl;
    }

    return 0;
}