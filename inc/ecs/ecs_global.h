#pragma once

#include "ecs.h"
#include <utils/hash_table.h>

#include <inttypes.h>

typedef struct kd_ecs_global
{
    hash_table  entities;
    bool        initialized;
} kd_ecs_global;

extern kd_ecs_global ecs_global;