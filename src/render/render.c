#include <render/render.h>
#include <render/render_internal.h>

#include <utils/logging.h>
#include <global.h>
#include <glad/glad.h>

#include <string.h>
#include <stdio.h>

int kdRenderInit()
{
    kdLogInit();
    
    memset(global.input.keys, KS_UNPRESSED, sizeof(global.input.keys));

    global.state.width = 800;
    global.state.height = 600;
    strcpy_s(
        global.state.title, 
        sizeof(global.state.title),
        "OpenGL Window");
    
    global.state.window = kdCreateWindow(
        global.state.width, 
        global.state.height, 
        global.state.title);

     if( !global.state.window )
        return -1;

    global.state.running = true;
    
    kdInitQuad(
        &global.int_state.vao,
        &global.int_state.vbo,
        &global.int_state.ebo,
        &global.int_state.program);

    global.int_state.texture = kdCreateTexture("assets/images/tile.png");
    mat4x4_ortho(
        global.int_state.projection, 
        -(float)global.state.width / 2.0f, 
        (float)global.state.width / 2.0f, 
        -(float)global.state.height / 2.0f, 
        (float)global.state.height / 2.0f, 
        -2, 2);
    
    glUseProgram(global.int_state.program);
    glUniformMatrix4fv(
        glGetUniformLocation(global.int_state.program, "projection"), 
        1, GL_FALSE, &global.int_state.projection[0][0]);

    glClearColor(0.15f, 0.15f, 0.25f, 1.0f);
    SDL_GL_SetSwapInterval(1);

    return 0;
}
void kdRenderDestroy()
{
    global.state.running = false;

    SDL_DestroyWindow(global.state.window);
    SDL_Quit();
}
void kdRenderBegin()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void kdRenderUpdate()
{
    kdUpdateInput(&global.input);

    SDL_PollEvent(&global.state.event);
    if (global.state.event.type == SDL_QUIT)
    {
        kdRenderDestroy();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);
}
void kdRenderEnd()
{
    SDL_GL_SwapWindow(global.state.window);
}

void kdSetTitle(const char* title)
{
    SDL_SetWindowTitle(global.state.window, title);
}
key_state kdGetKeyState(int key)
{
    return global.input.keys[key];
}
bool kdKeyIsPressed(int key)
{
    key_state state = global.input.keys[key];
    return ( (state == KS_PRESSED) || (state == KS_HOLD) );
}
bool kdShouldClose()
{
    return !global.state.running;
}
void kdRenderQuad(vec2 pos, vec3 color)
{
    static vec2 scale = {100,100};

    char title_buf[128];
    sprintf(title_buf, "pos = {%.2f, %.2f}; scale={%.2f, %.2f}", pos[0], pos[1], scale[0], scale[1]);
    kdSetTitle(title_buf);

    if( kdKeyIsPressed(KC_W) )
        pos[1] += 3.0f;
    if( kdKeyIsPressed(KC_A) )
        pos[0] -= 3.0f;
    if( kdKeyIsPressed(KC_S) )
        pos[1] -= 3.0f;
    if( kdKeyIsPressed(KC_D) )
        pos[0] += 3.0f;

    mat4x4 model;
    mat4x4_identity(model);
    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, scale[0], scale[1], 1);

    glBindVertexArray(global.int_state.vao);
    glUseProgram(global.int_state.program);
    glUniformMatrix4fv(
        glGetUniformLocation(global.int_state.program, "model"), 
        1, GL_FALSE, &model[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, global.int_state.texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
