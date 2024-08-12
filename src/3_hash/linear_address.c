#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

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
        index = (originalIndex + i) % SIZE;
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
        index = (originalIndex + i) % SIZE;
        i++;
    }

    return -1; // Key not found
}

void delete_value(HashTable *ht, int key)
{
    int index = hash(key);
    int originalIndex = index;
    int i = 1;

    while (ht->table[index].isOccupied)
    {
        if (ht->table[index].key == key)
        {
            ht->table[index].isOccupied = 0;
            return;
        }
        index = (originalIndex + i) % SIZE;
        i++;
    }
}

void print_table(HashTable *ht)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (ht->table[i].isOccupied)
        {
            printf("Index %d: Key = %d, Value = %d\n", i, ht->table[i].key, ht->table[i].value);
        }
        else
        {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main()
{
    HashTable ht;
    init_table(&ht);

    insert_value(&ht, 10, 100);
    insert_value(&ht, 20, 200);
    insert_value(&ht, 30, 300);
    insert_value(&ht, 40, 400);
    insert_value(&ht, 50, 500);

    print_table(&ht);

    printf("Search key 30: %d\n", search(&ht, 30));
    printf("Search key 60: %d\n", search(&ht, 60));

    delete_value(&ht, 30);
    print_table(&ht);

    return 0;
}