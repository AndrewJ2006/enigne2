#version 330 core
out vec4 FragColor;

in vec3 FragNormal;
in vec2 TexCoord;

uniform vec3 uColor;
uniform bool useTexture;
uniform sampler2D texture_diffuse1;

void main()
{
    if (useTexture) {
        vec4 texColor = texture(texture_diffuse1, TexCoord);
        if (texColor.a < 0.1)
            discard;
        FragColor = texColor;
    } else {
        FragColor = vec4(uColor, 1.0);
    }
}