#include <stdio.h>
#include <stdlib.h>

// we suggest hash function is key % size

struct ListNode;
typedef struct ListNode *Position;
typedef Position List;

#define MinTableSize 2

struct ListNode
{
    int val;
    Position next;
};

struct Hash
{
    int table_size;
    List *the_lists;
};

typedef struct Hash *HashTable;

HashTable init_table(int size)
{
    HashTable ht;
    int i;
    if (size < MinTableSize)
    {
        printf("Table size too small\n");
        return NULL;
    }

    ht = (HashTable)malloc(sizeof(struct Hash));
    if (ht == NULL)
    {
        printf("Out of space\n");
        return NULL;
    }
    ht->table_size = size;
    ht->the_lists = (List *)malloc(sizeof(List) * ht->table_size);
    if (ht->the_lists == NULL)
    {
        printf("Out of space\n");
        return NULL;
    }

    for (i = 0; i < ht->table_size; i++)
    {
        ht->the_lists[i] = (List)malloc(sizeof(struct ListNode));
        if (ht->the_lists[i] == NULL)
        {
            printf("Out of space\n");
            return NULL;
        }
        else
        {
            ht->the_lists[i]->next = NULL;
        }
    }
    return ht;
}

Position find(int key, HashTable ht)
{
    List l;
    Position pos;

    l = ht->the_lists[key % ht->table_size];
    pos = l->next;
    while (pos != NULL && pos->val != key)
    {
        pos = pos->next;
    }
    return pos;
}

void insert(int val, HashTable ht)
{
    Position pos, new_cell;
    List l;
    pos = find(val, ht);
    if (pos == NULL)
    {
        new_cell = (Position)malloc(sizeof(struct ListNode));
        if (new_cell == NULL)
        {
            printf("Out of space\n");
            return;
        }
        else
        {
            l = ht->the_lists[val % ht->table_size];
            new_cell->next = l->next;
            new_cell->val = val;
            l->next = new_cell;
        }
    }
}

void delete_node(int val, HashTable ht)
{
    Position pos, temp;
    List l;
    l = ht->the_lists[val % ht->table_size];
    pos = l;
    while (pos->next != NULL && pos->next->val != val)
    {
        pos = pos->next;
    }
    if (pos->next != NULL)
    {
        temp = pos->next;
        pos->next = temp->next;
        free(temp);
    }
}

void print_table(HashTable ht)
{
    int i;
    Position pos;
    for (i = 0; i < ht->table_size; i++)
    {
        printf("Table[%d]: ", i);
        pos = ht->the_lists[i]->next;
        while (pos != NULL)
        {
            printf("%d ", pos->val);
            pos = pos->next;
        }
        printf("\n");
    }
}

int main()
{
    HashTable ht;
    ht = init_table(5);
    for (int i = 1; i <= 10; i++)
    {
        insert(i, ht);
    }
    print_table(ht);
    for (int i = 1; i <= 10; i++)
    {
        delete_node(i, ht);
    }
    print_table(ht);
    return 0;
}