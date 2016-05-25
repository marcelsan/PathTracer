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
    void setOrtho(const vec2& min, const vec2& max);
    void setNPaths(unsigned n);
    void apply();
    void lookAt(const vec3& e, const vec3& c, const vec3& u);
    unsigned nPaths() const;
    Ray ray(float i, float j) const; // i and j must be between 0 and 1

private:
    glm::dmat4 M = glm::dmat4(1.0f);
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    vec2 clipMin = {-1.0, -1.0};
    vec2 clipMax = { 1.0,  1.0};

    float fov = M_PI/16.0;
    float aspect;
    unsigned npaths;
};

}

#endif