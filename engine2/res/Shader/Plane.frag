#version 330 core
out vec4 FragColor;

uniform vec3 uColor;
uniform bool useTexture;

void main()
{
    // For now, ignore textures and just use uColor
    FragColor = vec4(uColor, 1.0);
}