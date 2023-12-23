#pragma once

#include "keycodes.h"

typedef enum kd_key_state
{
    KS_UNPRESSED = 0,
    KS_PRESSED, KS_RELEASED, KS_HOLD
} key_state;

typedef struct kd_input
{
    key_state keys[512];
} kd_input;

extern void         kdUpdateInput(kd_input* input);