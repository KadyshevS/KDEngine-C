#include <ecs/ecs.h>
#include <ecs/ecs_global.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>

void ecs_init(size_t entities_count)
{
    if(ecs_global.initialized)
        return;

    ecs_global.entities = ht_create_table(entities_count);
    ecs_global.initialized = true;
}
entity ecs_create_entity(const char* name, size_t components_count)
{
    entity new_ent;
    strcpy_s(new_ent.name, 128, name);
    new_ent.componenets = ht_create_table(components_count);
    return new_ent;
}