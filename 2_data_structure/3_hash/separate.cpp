#include<iostream>
using namespace std;

const size_t MinSize = 2;

template<class T>
struct HashNode
{
    T val;
    HashNode *next;
};

template<class T>
struct HashTable
{
    int table_size;
    HashNode<T> **the_lists;
    HashTable(size_t size) : table_size(size)
    {
        the_lists = new HashNode<T> *[table_size];
        for (int i = 0; i < table_size; i++)
        {
            the_lists[i] = new HashNode<T>;
            the_lists[i]->next = nullptr;
        }
    }

    HashNode<T>* find_value(T val)
    {
        HashNode<T> *pos;
        size_t key = val % table_size;
        pos = the_lists[key];
        while (pos != nullptr && pos->val != val)
        {
            pos = pos->next;
        }
        return pos;
    }

    void insert_value(T val)
    {
        HashNode<T> *pos, *new_cell;
        size_t key = val % table_size;
        pos = find_value(val);
        if (pos == nullptr)
        {
            new_cell = new HashNode<T>;
            new_cell->val = val;
            new_cell->next = the_lists[key]->next;
            the_lists[key]->next = new_cell;
        }
    }
    void delete_value(T val)
    {
        HashNode<T> *pos, *tmp;
        size_t key = val % table_size;
        pos = the_lists[key];
        while (pos->next != nullptr && pos->next->val != val)
        {
            pos = pos->next;
        }
        if (pos->next != nullptr)
        {
            tmp = pos->next;
            pos->next = pos->next->next;
            delete tmp;
        }
    }
    void print_all()
    {
        HashNode<T> *pos;
        for (int i = 0; i < table_size; i++)
        {
            pos = the_lists[i]->next;
            while (pos != nullptr)
            {
                cout << pos->val << " ";
                pos = pos->next;
            }
        }
        cout << endl;
    }
};


int main(){
    HashTable<int> ht(MinSize);
    for(int i=0;i<10;i++){
        ht.insert_value(i);
    }
    ht.print_all();
    ht.delete_value(5);
    ht.print_all();
}