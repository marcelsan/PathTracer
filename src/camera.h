#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "ray.h"

using namespace glm;

namespace PathTrace {

struct Camera
{
public:
    void setEye(const vec3& eye);
    void setUp(const vec3& up);
    void setDir(const vec3& dir);
    Ray ray(const vec2& param) const;

private:
    vec3 eye;
    vec3 dir;
    vec3 up;
    vec2 clipMin = {-1.0, -1.0};
    vec2 clipMax = { 1.0,  1.0};
    float focusDistance = 1.0;

    vec3 vx, vy;
    vec3 focus;
    void updateVxVy();
};

}

#endif