#pragma once

typedef struct kd_data_element
{
    void*   data;
    int     size;
} data_element;

typedef struct kd_list
{
    data_element**  data;
    int             size;
    int             capacity;
} list;

extern list     list_create(int capacity);
extern void     list_insert(list* l, int index, void* data, int size);
extern void     list_delete(list* l, int index);
extern void     list_free(list* l);

extern void*    list_get(list* l, int index);
extern void*    list_get_ns(list* l, int index);