#version 330 core

in vec2 fTexCoord;

uniform sampler2D fTexture1;

out vec4 finalColor;

void main()
{
    finalColor = texture(fTexture1, fTexCoord);
}