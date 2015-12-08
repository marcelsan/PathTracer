#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>

namespace PathTrace {
typedef glm::vec3 color;
const color white = {1.0f, 1.0f, 1.0f};
const color black = {0.0f, 0.0f, 0.0f};
}

#endif