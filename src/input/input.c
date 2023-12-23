#include <input/input.h>
#include <utils/types.h>
#include <SDL2/SDL.h>

void kdUpdateInput(kd_input* input)
{
    SDL_PumpEvents();
    
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    for (int i = 0; i < 512; ++i)
    {
        switch (input->keys[i])
        {
        case KS_UNPRESSED:
            input->keys[i] = keystate[i] ? KS_PRESSED : KS_UNPRESSED;
            break;

        case KS_PRESSED:
            input->keys[i] = keystate[i] ? KS_HOLD : KS_RELEASED;
            break;

        case KS_RELEASED:
            input->keys[i] = keystate[i] ? KS_PRESSED : KS_UNPRESSED;
            break;

        case KS_HOLD:
            input->keys[i] = keystate[i] ? KS_HOLD : KS_RELEASED;
            break;
        }
    }
}