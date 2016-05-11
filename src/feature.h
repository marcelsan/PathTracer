#ifndef FEATURE_H
#define FEATURE_H

#include <vector>
#include <ostream>
#include "color.h"
#include "material.h"

namespace PathTrace {

struct Feature {
    Material mat;
    color col;
    glm::vec3 normal;
    float dist;
    bool positive = false;

    static const std::size_t feature_size = 18;

    std::vector<float> data() const {
        return {
            col.r,
            col.g,
            col.b,
            normal.x,
            normal.y,
            normal.z,
            dist,
            mat.color.r,
            mat.color.g,
            mat.color.b,
            mat.ka,
            mat.kd,
            mat.kt,
            mat.ks,
            mat.n,
            mat.ir,
            (mat.emissive ? 1.0 : -1.0),
            (positive ? 1.0 : -1.0)
        };
    }
};

}

#endif // FEATURE_H