#ifndef CAMERA_H
#define CAMERA_H
#include<glm/mat4x4.hpp>

class camera
{
private:
public:
    glm::mat4 camMat;
    camera();
    ~camera();
};
#endif