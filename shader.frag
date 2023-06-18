#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform int lights_size;
uniform vec3 lights[100];

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}