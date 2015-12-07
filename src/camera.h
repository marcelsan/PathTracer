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
    void setOrtho(const vec2& min, const vec2& max);
    Ray ray(float i, float j) const; // i and j must be between 0 and 1

private:
    vec3 eye;
    vec2 clipMin = {-1.0, -1.0};
    vec2 clipMax = { 1.0,  1.0};
    float focusDistance = 1.0;
};

}

#endif