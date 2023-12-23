#pragma once

#include "types.h"

typedef struct ht_node 
{
    char* key;
    void* value;
    struct ht_node* next;
} ht_node;

typedef struct kd_hash_table 
{
    ht_node** table;
    int size;
} hash_table;

u64             ht_hash(const char* str, int max_size);
hash_table      ht_create_table(int size);
void            ht_insert(hash_table* ht, const char* key, void* value);
void*           ht_get(hash_table* ht, const char* key);
void            ht_remove(hash_table* ht, const char* key);
void            ht_free(hash_table* ht);

// ht_node*        ht_create_node(const char* key, void* value);