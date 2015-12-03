#ifndef BOX_H
#define BOX_H

#include <glm/glm.hpp>
#include "object.h"
#include "intersection.h"

using namespace glm;

namespace PathTrace {

class Box : public Object
{
private:
    vec3 min, max;

public:
    Box();
    Box(vec3 min, vec3 max);
    ~Box();

    bool intersects(const Ray& ray) const;
};

}

#endif