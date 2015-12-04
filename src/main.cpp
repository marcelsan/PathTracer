
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

#include "material.h"
#include "scene.h"
#include "object.h"
#include "imagebuffer.h"
#include "color.h"
#include "filesystemutil.h"
#include "quadric.h"
#include "mesh.h"

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
	Camera cam;

	if (argc < 2)
		exit(-1);

	std::string path(argv[1]);
	FileSystemUtil::readSDLFile(path, cam, s);

	Material mat(vec3(1,0,0), 10.0, 1.0, 1.0, 1.0, 1);
	s.add(std::unique_ptr<Object>(new Quadric(10,2,3,4,5,6,7,8,9,0, mat)));

	ImageBuffer<color> ib(100, 100);

	return 0;
}