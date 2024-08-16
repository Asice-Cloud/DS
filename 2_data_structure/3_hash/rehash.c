#include <stdio.h>
#include <stdlib.h>

#define SIZE 7
#define SIZE_2 14

typedef struct
{
    int key;
    int value;
    int isOccupied;
} HashTableEntry;

typedef struct
{
    HashTableEntry *table;
    int size;
} HashTable;

void init_table(HashTable *ht, int size)
{
    ht->table = (HashTableEntry *)malloc(size * sizeof(HashTableEntry));
    ht->size = size;
    for (int i = 0; i < size; i++)
    {
        ht->table[i].isOccupied = 0;
    }
}

void insert_value(HashTable *ht, int key, int value)
{
    int index = key % ht->size;
    while (ht->table[index].isOccupied)
    {
        index = (index + 1) % ht->size;
    }
    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].isOccupied = 1;
}

HashTable ReHash(HashTable ht)
{
    HashTable new_ht;
    init_table(&new_ht, SIZE_2);
    for (int i = 0; i < ht.size; i++)
    {
        if (ht.table[i].isOccupied)
        {
            insert_value(&new_ht, ht.table[i].key, ht.table[i].value);
        }
    }
    free(ht.table);
    return new_ht;
}

int main()
{
    HashTable ht;
    init_table(&ht, SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        insert_value(&ht, i, i * i);
    }
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d %d %d\n", ht.table[i].key, ht.table[i].value, ht.table[i].isOccupied);
    }
    printf("\n");
    ht = ReHash(ht);
    for (int i = 0; i < SIZE_2; i++)
    {
        printf("%d %d %d\n", ht.table[i].key, ht.table[i].value, ht.table[i].isOccupied);
    }
    free(ht.table);
    return 0;
}