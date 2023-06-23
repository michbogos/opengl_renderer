#include<string>
#include<vector>
#include<glm/glm.hpp>
#include<glad/glad.h>
#ifndef SHADER_H
#define SHADER_H

class Shader
{
private:
    GLuint program;
    void(*setUniforms)(Shader shader);
public:
    Shader(std::string vertexShaderSource, std::string fragShaderSource, void(*setUniforms)(Shader shader));
    void use();
    void setUniform(float uniform, std::string uniformName);
    void setUniform(int uniform, std::string uniformName);
    void setUniform(glm::mat4x4 uniform, std::string uniformName);
    void setUniform(glm::vec3 uniform, std::string uniformName);
    void setUniform(std::vector<glm::vec3> data, std::string uniformName);
    ~Shader();
};

#endif