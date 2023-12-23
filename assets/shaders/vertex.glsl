#version 330 core
#pragma vertex

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTexCoord;

out vec2 fTexCoord;

uniform mat4x4 projection;
uniform mat4x4 model;

void main()
{
    gl_Position = projection * model * vec4(vPos, 1.0);
    fTexCoord = vTexCoord;
}