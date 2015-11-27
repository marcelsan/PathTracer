
#include <glm/glm.hpp>

#include "scene.h"
#include "object.h"
#include "imagebuffer.h"
#include "color.h"
#include <iostream>
#include <memory>

using namespace glm;
using namespace PathTrace;

int main(int argc, char const *argv[])
{
	vec3 x(1, 0, 0);
	vec3 y(0, 1, 0);
	vec3 z(0, 0, 1);

	color r(1, 0, 0);
	color g(0, 1, 0);
	color b(0, 0, 1);

	Quadric q(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, vec3(1,0,0), 10.0, 1.0, 1.0, 1.0, 1);
	q.getNormal();

	Scene s;
	ImageBuffer<color> ib(100, 100);

	return 0;
}