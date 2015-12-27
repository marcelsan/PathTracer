#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <glm/glm.hpp>

#include "ray.h"
#include "material.h"

using namespace glm;

namespace PathTrace {

struct Intersection {
    vec3 p;
    vec3 n;
    Material m;
};

}

#endif