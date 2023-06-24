#include<mesh.h>
#include<glad/glad.h>
#include <memory>
#include<iostream>
#include<string>
#include<utils.h>
#include<tiny_obj_loader.h>
#include <stb_image.h>

Mesh::Mesh(std::string file, std::shared_ptr<Shader> s, std::vector<Texture> texs){
    textures = texs;
    shader = s;
    textures.reserve(10);
    std::string inputfile = file;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), nullptr, true);

    if (!warn.empty()) {
    std::cout << warn << std::endl;
    }

    if (!err.empty()) {
    std::cerr << err << std::endl;
    }

    if (!ret) {
    exit(1);
    }

    
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            vertices.push_back({
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2],
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2],
                attrib.texcoords[2*index.texcoord_index+0],
                attrib.texcoords[2*index.texcoord_index+1]});
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nx));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));
    glEnableVertexAttribArray(2); 
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw(){
    glUseProgram(shader->program);
    int diff = 0;
    int spec = 0;
    int norm = 0;
    for(int i=0 ; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
        switch (textures[i].type)
        {
        case TextureType::diffuse:
            shader->setUniform(i, "DIFFUSE_" + std::to_string(diff));
            diff++;
            break;
        case TextureType::specular:
            shader->setUniform(i, "SPECULAR_" + std::to_string(spec));
            spec++;
            break;
        case TextureType::normal:
            shader->setUniform(i, "NORMAL_" + std::to_string(norm));
            norm ++;
            break;
        
        default:
            shader->setUniform(i, "DIFFUSE_" + std::to_string(diff));
            diff++;
            break;
        }
    }
    shader->setUniforms(*shader);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::addTexture(std::string filename, TextureType type){
    Texture texture;
    texture.type = type;
    std::cout << texture.id << "\n";
    glGenTextures(1, &texture.id);
    std::cout << texture.id << "\n";
    glBindTexture(GL_TEXTURE_2D, texture.type);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        textures.push_back(texture);
    }
    else{
        std::cout << "Failed to load image: " << filename << "\n";
    }

    stbi_image_free(data);
}

Mesh::~Mesh()
{
    for(Texture texture : textures){
        glDeleteTextures(1, &texture.id);
    }
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}