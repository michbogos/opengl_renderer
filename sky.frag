#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D DIFFUSE_0;

void main()
{    
    FragColor = texture(DIFFUSE_0, TexCoord);
}