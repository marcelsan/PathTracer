#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

namespace PathTrace {

struct AABB {
	glm::vec3 min;
	glm::vec3 max;

	AABB() {}
};

}

#endif