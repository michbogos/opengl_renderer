#include<glm/glm.hpp>
#include<vector>
#include<string>

struct Vertex{
    float x;
    float y;
    float z;
    float u;
    float v;
};

class mesh
{
private:
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    unsigned int VAO, VBO, EBO;
public:
    mesh();
    mesh(std::string file);
    void draw();
    ~mesh();
};


