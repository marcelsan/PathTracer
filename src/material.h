#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

using namespace glm;

namespace PathTrace {
class Material {
public:
    Material();
    Material(vec3 color, float ka, float kd, float ks, float kt, int n);

    vec3 color;
    float ka, kd, ks, kt;
    int n;
};

}

#endif