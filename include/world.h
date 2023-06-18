#include<glm/glm.hpp>
#include<shader.h>
#include<vector>

#ifndef WORLD_H
#define WORLD_H

struct Light{
    glm::vec3 pos;
    glm::vec3 color;
    float intensity;
};

class world
{
private:
    std::vector<Light> lights;
public:
    world();
    void addLight(Light light);
    void giveLightInformation(shader &s);
    ~world();
};
#endif