#ifndef RAYTRACE_H
#define RAYTRACE_H

#include "scene.h"
#include "size.h"
#include "camera.h"

namespace PathTrace {

void pathtrace(std::string filename, const Size& size, const Scene& scene, const Camera& cam);

}

#endif