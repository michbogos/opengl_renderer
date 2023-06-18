#include<world.h>

#include<vector>
#include<algorithm>

world::world()
{
}

void world::addLight(Light light){
    lights.push_back(light);
}

void world::giveLightInformation(shader &s){
    s.use();
    std::vector<glm::vec3> light_pos(lights.size());
    for(int i = 0; i < lights.size(); i++){
        light_pos[i] = lights[i].pos;
    }
    s.setUniform((int)lights.size(), "lights_size");
    s.setUniform(light_pos, "lights");
}

world::~world()
{
}
