#include <shader.h>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<mesh.h>
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <vector>

Shader::Shader(std::string vertexShaderSource, std::string fragmentShaderSource, void(*setUniformsFunction)(Shader shader))
{
    setUniforms = setUniformsFunction;
    if(!std::filesystem::exists(vertexShaderSource) || !std::filesystem::exists(fragmentShaderSource)){
        throw std::runtime_error("Shader file does not exist!");
    }
    std::ifstream vShaderFile(vertexShaderSource);
    std::stringstream vShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    std::string vShaderString = vShaderStream.str();
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vStr = vShaderString.c_str();
    glShaderSource(vShader, 1, &vStr, NULL);
    glCompileShader(vShader);
    int success;
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    std::ifstream fShaderFile(fragmentShaderSource);
    std::stringstream fShaderStream;
    fShaderStream << fShaderFile.rdbuf();
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fShaderString = fShaderStream.str();
    const char* fStr = fShaderString.c_str();
    glShaderSource(fShader, 1, &fStr, NULL);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    vShaderFile.close();
    fShaderFile.close();
}

void Shader::use(){
    glUseProgram(program);
    setUniforms(*this);

}

void Shader::setUniform(float uniform, std::string uniformName){
    uint32_t loc = glGetUniformLocation(program, uniformName.c_str());
    glUniform1f(loc, uniform);
}

void Shader::setUniform(int uniform, std::string uniformName){
    uint32_t loc = glGetUniformLocation(program, uniformName.c_str());
    glUniform1i(loc, uniform);
}

void Shader::setUniform(glm::mat4x4 uniform, std::string uniformName){
    uint32_t loc = glGetUniformLocation(program, uniformName.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(uniform));
}

void Shader::setUniform(glm::vec3 uniform, std::string uniformName){
    uint32_t loc = glGetUniformLocation(program, uniformName.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(uniform));
}

void Shader::setUniform(std::vector<glm::vec3> data, std::string uniformName){
    uint32_t loc = glGetUniformLocation(program, uniformName.c_str());
    float arr[data.size()*3];
    for(int i = 0; i < data.size(); i += 3){
        arr[i] = data[i].x;
        arr[i+1] = data[i].y;
        arr[i+2] = data[i].z;
    } 
    glUniform3fv(loc, data.size(), arr);
}

void Shader::cleanup(){
    glDeleteProgram(program);
    std::cout << "Deleting Shader " << program << "\n";
}

Shader::~Shader()
{
//     std::cout << "Deleting Shader\n";
}
