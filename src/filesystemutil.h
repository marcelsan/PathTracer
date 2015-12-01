#pragma once

#include <string>
#include "scene.h"

namespace FileSystemUtil
{
void readSDLFile(const std::string& path, PathTrace::Scene& s);
}