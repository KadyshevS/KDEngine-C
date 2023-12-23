#include <utils/list.h>

#include <stdlib.h>
#include <memory.h>
#include <assert.h>

list list_create(int capacity)
{
    if (capacity <= 0)
        capacity = 1;
    
    list new_list;
    new_list.capacity = capacity;
    new_list.size = 0;
    new_list.data = (data_element**)malloc(capacity * sizeof(data_element*));

    assert("Failed to allocate memory for list." && new_list.data);

    return new_list;
}

void list_insert(list* l, int index, void* data, int size)
{
    if (!l)
        return;

    if (index < 0 || index > l->size)
        index = !l->size ? 0 : l->size-1;

    if (l->size == l->capacity)
    {
        int new_capacity = l->capacity * 2;
        data_element** new_data = (data_element**)realloc(l->data, new_capacity * sizeof(data_element*));

        if (!new_data)
            return;

        l->data = new_data;
        l->capacity = new_capacity;
    }

    for (int i = l->size; i > index; i--)
    {
        l->data[i] = l->data[i - 1];
    }

    l->data[index] = (data_element*)malloc(sizeof(data_element));
    l->data[index]->data = malloc(size);
    memcpy(l->data[index]->data, data, size);
    l->data[index]->size = size;
    l->size++;
}

void list_delete(list* l, int index)
{
    if (!l || index < 0 || index >= l->size)
        return;

    free(l->data[index]->data);
    free(l->data[index]);

    for (int i = index; i < l->size - 1; i++)
    {
        l->data[i] = l->data[i + 1];
    }

    l->size--;
}

void list_free(list* l)
{
    if (!l)
        return;

    for (int i = 0; i < l->size; i++)
    {
        free(l->data[i]->data);
    }

    free(l->data);
}

void* list_get(list* l, int index)
{
    if(index < 0 || index >= l->size)
        return NULL;

    return l->data[index]->data;
}

void* list_get_ns(list* l, int index)
{
    return l->data[index]->data;
}