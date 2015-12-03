#ifndef FILESYSTEMUTIL_H
#define FILESYSTEMUTIL_H

#include <string>
#include "scene.h"
#include "mesh.h"

namespace FileSystemUtil
{
void readSDLFile(const std::string& path, PathTrace::Scene& s);
void readOBJFile(const std::string& path, PathTrace::Mesh& m);
}

#endif