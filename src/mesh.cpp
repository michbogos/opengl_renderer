#include<mesh.h>
#include<glad/glad.h>
#include<iostream>
#include<string>
#include<tiny_obj_loader.h>

mesh::mesh()
{
    // vertices.push_back(-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back( 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 0.0f},});
    // vertices.push_back(-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f},});    for(int i = 0; i < 36; i++){
    //     indices.push_back(i);
    // }

    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(float)));
    // glEnableVertexAttribArray(1); 
    // glBindVertexArray(0);
}

mesh::mesh(std::string file){
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
            attrib.vertices[3 * index.vertex_index + 2], 0.0f, 0.0f});
        indices.push_back(indices.size());
    }
}

    for(auto index : indices){
        std::cout << index << "\n";
    }

    for(auto vertex : vertices){
        std::cout << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*5*sizeof(float), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); 
    glBindVertexArray(0);
}

void mesh::draw(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

mesh::~mesh()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}