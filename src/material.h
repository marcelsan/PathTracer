#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

using namespace glm;

namespace PathTrace {
class Material {
public:
    Material();
    Material(vec3 color, float ka, float kd, float ks, float kt, int n, float ir = -1.f, bool emissive = false);

    float ktot() const { return kd + ks + kt; }
    vec3 color;
    float ka, kd, ks, kt;
    int n;
    float ir;
    bool emissive = false;
};

}

#endif