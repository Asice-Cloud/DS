#include <stdio.h>
#include <stdlib.h>

#define SIZE 19

typedef struct
{
    int key;
    int value;
    int isOccupied;
} HashTableEntry;

typedef struct
{
    HashTableEntry table[SIZE];
} HashTable;

int hash(int key)
{
    return key % SIZE;
}

int hash2(int key)
{
    return 7 - (key % 7);
}

void init_table(HashTable *ht)
{
    for (int i = 0; i < SIZE; i++)
    {
        ht->table[i].isOccupied = 0;
    }
}

void insert_value(HashTable *ht, int key, int value)
{
    int index = hash(key);
    int originalIndex = index;
    int i = 1;

    while (ht->table[index].isOccupied)
    {
        index = (originalIndex + i * hash2(key)) % SIZE;
        i++;
    }

    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].isOccupied = 1;
}

int search(HashTable *ht, int key)
{
    int index = hash(key);
    int originalIndex = index;
    int i = 1;

    while (ht->table[index].isOccupied)
    {
        if (ht->table[index].key == key)
        {
            return ht->table[index].value;
        }
        index = (originalIndex + i * hash2(key)) % SIZE;
        i++;
    }

    return -1;
}

int main()
{
    HashTable ht;
    init_table(&ht);

    for (int i = 0; i < SIZE; i++)
    {
        insert_value(&ht, i, i * i);
    }

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d\n", search(&ht, i));
    }

    return 0;
}
