#include<glm/glm.hpp>
#include<vector>

struct Vertex{
    glm::vec3 pos;
    glm::vec2 tex;
};

class mesh
{
private:
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    unsigned int VAO, VBO, EBO;
public:
    mesh();
    void draw();
    ~mesh();
};


