#pragma once

#include "types.h"

typedef struct kd_image
{
    i32 width, height;
    i32 channels;
    u8* data;
} kd_image;

extern char*        file_to_str(const char* filename);
extern kd_image*    load_image(const char* filename);
extern void         free_image(kd_image* img);