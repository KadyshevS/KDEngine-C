#pragma once

#include <utils/hash_table.h>

typedef struct kd_entity
{
    char            name[128];
    hash_table      componenets;
} entity;

extern void     ecs_init(size_t entities_count);
extern entity   ecs_create_entity(const char* name, size_t components_count);