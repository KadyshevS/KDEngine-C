#include <render/render_internal.h>

#include <sdl.h>

#include <utils/logging.h>
#include <utils/file.h>
#include <glad/glad.h>

SDL_Window* kdCreateWindow(u32 width, u32 height, const char* title)
{
    SDL_Window* window;
    
    if( SDL_Init(SDL_INIT_VIDEO) )
    {
        kdLog("Failed to initialize SDL.");
        return NULL;
    }
    
    window = SDL_CreateWindow(
        "Test Window", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_OPENGL);

    if( !window )
    {
        kdLog("Failed to create window.");
        return NULL;
    }
    
    SDL_GL_CreateContext(window);
    if( !gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) )
    {
        kdLog("Failed to load OpenGL.");

        SDL_DestroyWindow(window);
        return NULL;
    }

    return window;
}
u32 kdCreateProgram(const char* v_shader_path, const char* f_shader_path)
{
    u32 out_prg;
    u32 v_mdl;
    u32 f_mdl;

    char* v_src = file_to_str(v_shader_path);
    if(!v_src) exit(1);
    char* f_src = file_to_str(f_shader_path);
    if(!f_src) exit(1);

    char log[512];
    int success;

    v_mdl = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_mdl, 1, (const char* const*)&v_src, NULL);
    glCompileShader(v_mdl);
    glGetShaderiv(v_mdl, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(v_mdl, 512, NULL, log);
        kdLog("Failed to compile vertex shader:\n");
        kdLog(log);

        exit(1);
    }

    f_mdl = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_mdl, 1, (const char* const*)&f_src, NULL);
    glCompileShader(f_mdl);
    glGetShaderiv(f_mdl, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(f_mdl, 512, NULL, log);
        kdLog("Failed to compile fragment shader:\n");
        kdLog(log);

        exit(1);
    }

    out_prg = glCreateProgram();
    glAttachShader(out_prg, v_mdl);
    glAttachShader(out_prg, f_mdl);
    glLinkProgram(out_prg);
    glGetProgramiv(out_prg, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(out_prg, 512, NULL, log);
        kdLog("Failed to link shaders:\n");
        kdLog(log);

        exit(1);
    }
    
    free(v_src);
    free(f_src);

    return out_prg;
}

void kdInitQuad(u32* vao, u32* vbo, u32* ebo, u32* program)
{
    f32 vertices[] = 
    {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    u32 indices[] = 
    {
        0, 1, 2,    0, 2, 3
    };

    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glGenBuffers(1, ebo);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(f32)*5, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(f32)*5, (void*)(sizeof(f32)*3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    *program = kdCreateProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

u32 kdCreateTexture(const char* filename)
{
    u32 out_texture;
    kd_image* image = load_image(filename);
    
    glGenTextures(1, &out_texture);
    glBindTexture(GL_TEXTURE_2D, out_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
    glGenerateMipmap(GL_TEXTURE_2D);

    free_image(image);

    return out_texture;
}