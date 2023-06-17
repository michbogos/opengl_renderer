#include<mesh.h>
#include<glad/glad.h>
#include<iostream>

mesh::mesh()
{
    vertices.push_back({{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{ 0.5f, -0.5f, -0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{ 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{ 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{ 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{ 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{ 0.5f, -0.5f,  0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{ 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f},});
    vertices.push_back({{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f},});
    vertices.push_back({{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f},});
    vertices.push_back({{-0.5f,  0.5f,  0.5f},  {0.0f, 0.0f},});
    vertices.push_back({{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f},});

    for(int i = 0; i < 36; i++){
        indices.push_back(i);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); 
    glBindVertexArray(0);
}

void mesh::draw(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

mesh::~mesh()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}