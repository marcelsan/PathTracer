#ifndef RAYTRACE_H
#define RAYTRACE_H

#include "scene.h"
#include "size.h"
#include "camera.h"
#include "npywriter.h"

namespace PathTrace {

void pathtrace(NPYWriter &writer, const Size& size, const Scene& scene, const Camera& cam);

}

#endif