#include<mesh.h>
#include<glad/glad.h>
#include <memory>
#include<iostream>
#include<string>
#include<tiny_obj_loader.h>
#include <stb_image.h>

Mesh::Mesh(std::string file,std::vector<TextureInfo> texs){
    for(auto tex:texs){
        int width, height, nrChannels;
        unsigned char* data = stbi_load(tex.filepath.c_str(), &width, &height, &nrChannels, 3);
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        textures.push_back({texture, tex.type});
    }
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
                0, 0, 0,
                attrib.texcoords[2*index.texcoord_index+0],
                attrib.texcoords[2*index.texcoord_index+1],});
        }
    }

    for(int i = 0; i < vertices.size(); i+=3){
        auto v0 = vertices[i];
        auto v1 = vertices[i+1];
        auto v2 = vertices[i+2];

        glm::vec3 e1 = {v1.x-v0.x, v1.y-v0.y, v1.z-v0.z};
        glm::vec3 e2 = {v2.x-v0.x, v2.y-v0.y, v2.z-v0.z};

        glm::vec2  duv1 = {v1.u-v0.u, v1.v-v0.v};
        glm::vec2  duv2 = {v2.u-v0.u, v2.v-v0.v};

        float f = 1.0f / (duv1.x*duv2.y - duv2.x*duv1.y);

        glm::vec3 tangent;

        tangent.x = f * (duv2.y * e1.x - duv1.y * e2.x);
        tangent.y = f * (duv2.y * e1.y - duv1.y * e2.y);
        tangent.z = f * (duv2.y * e1.z - duv1.y * e2.z);

        vertices[i+0].tx += tangent.x;
        vertices[i+0].ty += tangent.y;
        vertices[i+0].tz += tangent.z;

        vertices[i+1].tx += tangent.x;
        vertices[i+1].ty += tangent.y;
        vertices[i+1].tz += tangent.z;

        vertices[i+2].tx += tangent.x;
        vertices[i+2].ty += tangent.y;
        vertices[i+2].tz += tangent.z;

    }

    for(int i = 0; i < vertices.size(); i++){
        glm::vec3 t = {vertices[i].tx, vertices[i].ty, vertices[i].tz};
        t = glm::normalize(t);
        vertices[i].tx = t.x;
        vertices[i].ty = t.y;
        vertices[i].tz = t.z;
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

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tx));
    glEnableVertexAttribArray(2); 

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));
    glEnableVertexAttribArray(3); 

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw(Shader shader){
    glUseProgram(shader.program);
    int diff = 0;
    int spec = 0;
    int norm = 0;
    for(int i=0 ; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
        if(textures[i].type == TextureType::diffuse){
            shader.setUniform(i, "DIFFUSE_" + std::to_string(diff));
            diff++;
        }
        if(textures[i].type == TextureType::specular){
            shader.setUniform(i, "SPECULAR_" + std::to_string(spec));
            spec++;
        }
        if(textures[i].type == TextureType::normal){
            shader.setUniform(i, "NORMAL_" + std::to_string(norm));
            norm++;
        }
    }
    shader.setUniforms(shader);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Mesh::addTexture(std::string filename, TextureType type){
    Texture texture;
    texture.type = type;
    glGenTextures(1, &texture.id);
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

void Mesh::cleanup(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

    for(auto texture:textures){
        glDeleteTextures(1, &texture.id);
    }
}

Mesh::~Mesh()
{ 
}