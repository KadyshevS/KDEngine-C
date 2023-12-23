#pragma once

#include <sdl.h>
#include <utils/types.h>
#include <input/input.h>
#include <linmath/linmath.h>

typedef struct kd_render_state
{
    SDL_Window*     window;
    SDL_Event       event;
    u32             width, 
                    height;
    char            title[256];
    bool            running;
} render_state;

extern int          kdRenderInit();
extern void         kdRenderDestroy();
extern void         kdRenderBegin();
extern void         kdRenderUpdate();
extern void         kdRenderEnd();

extern void         kdRenderQuad(vec2 pos, vec3 color);

extern void         kdSetTitle(const char* title);
extern key_state    kdGetKeyState(int key);
extern bool         kdKeyIsPressed(int key);
extern bool         kdShouldClose();