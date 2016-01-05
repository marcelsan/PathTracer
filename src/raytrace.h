#ifndef RAYTRACE_H
#define RAYTRACE_H

#include "imagebuffer.h"
#include "scene.h"
#include "camera.h"

namespace PathTrace {

void raytrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam);
void pathtrace(ImageBuffer &buffer, const Scene& scene, const Camera& cam);

}

#endif