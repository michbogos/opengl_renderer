#include<glm/glm.hpp>
#include<vector>
#include<string>

struct Vertex{
    glm::vec3 pos;
    glm::vec3 tex;
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


