#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <memory>

#include "scene.h"

namespace FileSystemUtil
{
void readSDLFile(const std::string& path, PathTrace::Scene& s);
}