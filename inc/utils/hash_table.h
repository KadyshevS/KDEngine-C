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
    size_t size;
    size_t capacity;
} hash_table;

size_t          ht_hash(const char* str, size_t max_size);
hash_table      ht_create_table(size_t size);
void            ht_insert(hash_table* ht, const char* key, void* value);
void*           ht_get(hash_table* ht, const char* key);
void            ht_remove(hash_table* ht, const char* key);
void            ht_free(hash_table* ht);

// ht_node*        ht_create_node(const char* key, void* value);