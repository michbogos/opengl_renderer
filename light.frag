#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = vec4(1,1,1,1);
}