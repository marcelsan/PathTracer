
#include <glm/glm.hpp>

#include "scene.h"
#include "imagebuffer.h"
#include "color.h"

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

	Scene s;
	ImageBuffer<color> ib(100, 100);

	return 0;
}