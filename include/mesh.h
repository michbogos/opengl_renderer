#include<glm/glm.hpp>
#include<vector>
#include<string>
#include<memory>
#include<shader.h>

#ifndef MESH_H
#define MESH_H

struct Vertex{
    float x;
    float y;
    float z;
    float nx;
    float ny;
    float nz;
    float tx;
    float ty;
    float tz;
    float u;
    float v;
};

enum TextureType{
    diffuse, specular, normal
};

struct Texture{
    unsigned int id;
    TextureType type;
};

class Mesh
{
private:
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::shared_ptr<Shader> shader;
    unsigned int VAO, VBO, EBO;
public:
    Mesh(std::string file, std::shared_ptr<Shader> shader, std::vector<Texture> texs);
    void draw();
    void addTexture(std::string filename, TextureType type);
    ~Mesh();
};

#endif
