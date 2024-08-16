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
        index = (originalIndex + i * i) % SIZE;
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
        index = (originalIndex + i * i) % SIZE;
        i++;
    }

    return -1;
}

int main()
{
    HashTable ht;
    init_table(&ht);

    insert_value(&ht, 1, 10);
    insert_value(&ht, 2, 20);
    insert_value(&ht, 3, 30);
    insert_value(&ht, 4, 40);
    insert_value(&ht, 5, 50);

    printf("Value for key 1: %d\n", search(&ht, 1));
    printf("Value for key 2: %d\n", search(&ht, 2));
    printf("Value for key 3: %d\n", search(&ht, 3));
    printf("Value for key 4: %d\n", search(&ht, 4));
    printf("Value for key 5: %d\n", search(&ht, 5));

    return 0;
}
