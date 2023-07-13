#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D DIFFUSE_0;

void main()
{    
    FragColor = vec4(texture(DIFFUSE_0, TexCoord).xyz, 1.0);
}