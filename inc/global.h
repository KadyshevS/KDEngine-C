#pragma once

#include <render/render.h>
#include <render/render_internal.h>
#include <input/input.h>

typedef struct kd_global
{
    render_state            state;
    render_internal_state   int_state;
    kd_input                input;
} kd_global;

extern kd_global global;