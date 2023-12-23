#include <stdio.h>
#include <stdlib.h>

#include <utils/hash_table.h>

typedef struct human
{
    int age;
    int course;
} human;

int main(void)
{
    //  hash table
    hash_table ht1 = ht_create_table(128);

    human* anst = (human*)malloc(sizeof(human));
    human* geor = (human*)malloc(sizeof(human));
    
    anst->age = 18;
    anst->course = 3;

    geor->age = 14;
    geor->course = 2;

    ht_insert(&ht1, "Sergei", anst);

    anst = (human*)ht_get(&ht1, "Sergei");
    anst->age = 12;
    anst->course = 1;

    printf("\tage: %d\n\tcourse: %d\n", anst->age, anst->course);

    ht_insert(&ht1, "Georgy", anst);

    geor = (human*)ht_get(&ht1, "Georgy");
    geor->age = 32;
    geor->course = 54;

    printf("\n\tage: %d\n\tcourse: %d\n", geor->age, geor->course);

    ht_free(&ht1);

    system("pause");
    return 0;
}

// #include <engine.h>

// int main(void)
// {
//     kdRenderInit();

//     vec2 pos1 = {0.0f, 0.0f};
//     vec2 pos2 = {150.0f, 150.0f};

//     vec3 color1 = {0.2f, 0.8f, 0.3f};
//     vec3 color2 = {0.2f, 0.3f, 0.8f};

//     while( !kdShouldClose() )
//     {
//         kdRenderUpdate();

//         kdRenderBegin();
//         kdRenderQuad(pos1, color1);
//         kdRenderQuad(pos2, color2);
//         kdRenderEnd();
//     }

//     return 0;
// }