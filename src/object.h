#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "ray.h"
#include "material.h"
#include "intersection.h"

using namespace glm;

namespace PathTrace {

class Object {
public:
    Object();
    Object(const Material& m);
    virtual ~Object();
    virtual Intersection intersect(const Ray& ray) const = 0;

private:
	Material mat;
};

}

#endif