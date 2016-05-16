#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <iostream>
#include "ray.h"

using namespace glm;

namespace PathTrace {

struct Camera
{
public:
    void setAspect(float a);
    void setEye(const vec3& eye);
    void setRot(const vec3& rot);
    void setOrtho(const vec2& min, const vec2& max);
    void setNPaths(unsigned n);
    unsigned nPaths() const;
    Ray ray(float i, float j) const; // i and j must be between 0 and 1

private:
    vec3 eye;
    vec3 rot;
    vec2 clipMin = {-1.0, -1.0};
    vec2 clipMax = { 1.0,  1.0};

    float fov = M_PI/8.0;
    float aspect;
    unsigned npaths;
};

}

#endif