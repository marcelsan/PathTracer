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
    float sec_dist;
    bool positive = false;

    static const std::size_t feature_size = 19;

    std::vector<float> data() const {
        return {
            col.r,
            col.g,
            col.b,
            normal.x,
            normal.y,
            normal.z,
            dist,
            sec_dist,
            mat.color.r,
            mat.color.g,
            mat.color.b,
            mat.ka,
            mat.kd,
            mat.ks,
            mat.kt,
            static_cast<float>(mat.n),
            mat.ir,
            (mat.emissive ? 1.0f : -1.0f),
            (positive ? 1.0f : -1.0f)
        };
    }
};

}

#endif // FEATURE_H