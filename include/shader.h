#include<string>
#include<vector>
#include<glm/glm.hpp>
#include<glad/glad.h>
#ifndef SHADER_H
#define SHADER_H

class shader
{
private:
    GLuint program;
public:
    shader(std::string vertexShaderSource, std::string fragShaderSource);
    void use();
    void setUniform(float uniform, std::string uniformName);
    void setUniform(int uniform, std::string uniformName);
    void setUniform(glm::mat4x4 uniform, std::string uniformName);
    void setUniform(std::vector<glm::vec3> data, std::string uniformName);
    ~shader();
};

#endif