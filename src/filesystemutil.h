#ifndef FILESYSTEMUTIL_H
#define FILESYSTEMUTIL_H

#include <string>
#include "scene.h"
#include "mesh.h"

namespace FileSystemUtil
{
static void readSDLFile(const std::string& path, PathTrace::Scene& s);
void readOBJFile(const std::string& url, PathTrace::Mesh& m);
}

#endif