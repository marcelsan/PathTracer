#ifndef QUADRIC_H
#define QUADRIC_H

#include "object.h"

using namespace glm;

namespace PathTrace {

class Quadric : public Object {
public:
    Quadric();
    Quadric(float a, float b, float c, float d, float e,
            float f, float g, float h, float i, float j,
            const Material& m = {});
    virtual ~Quadric();

    bool intersect(const Ray& ray, Intersection& inter) const;
    vec3 samplePosition() const;
    const vec3 normal(vec3 point) const;

private:
    float  a, b, c, d, e; // Coefficents of equation of..
    float  f, g, h, i, j; // ... quadric surface
};

}

#endif