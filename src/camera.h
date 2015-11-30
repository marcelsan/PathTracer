#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

using namespace glm;

namespace PathTrace {

class Camera
{
public:
    Camera();
    Camera(vec3 eye);
    ~Camera();

private:
    vec3 eye;
};
}

#endif