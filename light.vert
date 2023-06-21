#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4x4 mat;
uniform mat4x4 world;
uniform mat4x4 view;
uniform mat4x4 proj;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    gl_Position = proj * view * world * mat * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    FragPos = vec3(world * mat* vec4(aPos, 1.0));
    Normal = vec3(mat*vec4(aNormal, 0.0));
}
