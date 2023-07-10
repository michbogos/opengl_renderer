#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 mat;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = proj * view * mat * vec4(aPos, 1.0);
}  