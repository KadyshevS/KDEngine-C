#include <utils/hash_table.h>
#include <stdlib.h>
#include <string.h>

u64 ht_hash(const char* str, int max_size) 
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % max_size;
}

hash_table ht_create_table(int size)
{
    hash_table ht_return = {0};
    ht_return.size = size;
    ht_return.table = (ht_node**)calloc(size, sizeof(ht_node*));

    return ht_return;
}

ht_node* ht_create_node(const char* key, void* value) 
{
    ht_node* new_node = (ht_node*)malloc(sizeof(ht_node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void ht_insert(hash_table* ht, const char* key, void* value) 
{
    unsigned long index = ht_hash(key, ht->size);
    ht_node* new_node = ht_create_node(key, value);

    if (ht->table[index] == NULL) 
    {
        ht->table[index] = new_node;
    } 
    else 
    {
        new_node->next = ht->table[index];
        ht->table[index] = new_node;
    }
}

void* ht_get(hash_table* ht, const char* key) 
{
    unsigned long index = ht_hash(key, ht->size);
    ht_node* current = ht->table[index];

    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0) 
        {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void ht_remove(hash_table* ht, const char* key) 
{
    unsigned long index = ht_hash(key, ht->size);
    ht_node* current = ht->table[index];
    ht_node* prev = NULL;

    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0) 
        {
            if (prev == NULL) 
            {
                ht->table[index] = current->next;
            } 
            else 
            {
                prev->next = current->next;
            }

            free(current->key);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

void ht_free(hash_table* ht) 
{
    for (int i = 0; i < ht->size; i++) 
    {
        ht_node* current = ht->table[i];
        while (current != NULL) 
        {
            ht_node* next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
}