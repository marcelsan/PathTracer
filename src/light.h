#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "mesh.h"

using namespace glm;

namespace PathTrace {

class Light
{
public:
    Light();
private:
    float Ip;
    color c;
    Mesh light;
};

}

#endif