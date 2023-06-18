#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4x4 mat;
uniform mat4x4 world;
uniform mat4x4 view;
uniform mat4x4 proj;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = proj*view*mat*vec4(aPos, 1.0);
}
