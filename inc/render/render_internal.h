#pragma once

#include <sdl.h>
#include <utils/types.h>
#include <linmath/linmath.h>

typedef struct kd_render_internal_state
{
    u32 vao;
    u32 vbo;
    u32 ebo;
    u32 program;
    u32 texture;

    mat4x4 projection;
} render_internal_state;

extern SDL_Window*  kdCreateWindow(u32 width, u32 height, const char* title);
extern u32          kdCreateProgram(const char* v_shader_path, const char* f_shader_path);
extern u32          kdCreateTexture(const char* filename);

extern void         kdInitQuad(u32* vao, u32* vbo, u32* ebo, u32* program);