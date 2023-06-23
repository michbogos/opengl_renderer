#include<glm/glm.hpp>
#include<vector>
#include<string>
#include<memory>
#include<shader.h>

struct Vertex{
    float x;
    float y;
    float z;
    float nx;
    float ny;
    float nz;
    float u;
    float v;
};

class mesh
{
private:
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    std::shared_ptr<Shader> shader;
    unsigned int VAO, VBO, EBO;
public:
    mesh(std::string file, std::shared_ptr<Shader> shader);
    void draw();
    ~mesh();
};


