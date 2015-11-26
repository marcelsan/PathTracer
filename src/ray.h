#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <iostream>

using namespace glm;

namespace PathTrace {

struct Ray {
    vec3 o, d;
};

}

#endif