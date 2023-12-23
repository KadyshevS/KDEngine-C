#pragma once

#include <utils/hash_table.h>

typedef struct kd_entity
{
    char            name[128];
    hash_table      componenets;
    uint32_t        componenets_count;
} entity;
