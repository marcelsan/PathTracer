#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

using namespace glm;

namespace PathTrace {
class Material {
public:
    Material();
    Material(vec3 color, float ka, float kd, float ks, float kt, int n, float ir = -1.f, bool emissive = false);

    vec3 color;
    float ka, kd, ks, kt, ir;
    int n = 2;
    bool emissive = false;
};

}

#endif