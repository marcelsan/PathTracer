#ifndef SDLREADER_H
#define SDLREADER_H

#include <string>
#include "camera.h"
#include "size.h"
#include "mesh.h"
#include "scene.h"

namespace PathTrace {
namespace SDLReader {
void readSDLFile(const std::string& path, PathTrace::Size& size, PathTrace::Camera& cam, PathTrace::Scene& s);
void readOBJFile(const std::string& path, PathTrace::Mesh& m);
}
}

#endif