#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "ray.h"
#include "light.h"
#include "material.h"
#include "intersection.h"

using namespace glm;

namespace PathTrace {

class Object {
private:
    Material mat;

public:
	Object();
    Object(const Material& m);
    virtual ~Object();
    virtual bool intersect(const Ray& ray, Intersection& inter) const = 0;
    virtual vec3 samplePosition() const = 0;

protected:
	const Material& material() const { return mat; }
};

}

#endif