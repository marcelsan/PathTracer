
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "scene.h"
#include "sdlreader.h"
#include "raytrace.h"

using namespace glm;
using namespace PathTrace;

int main(int argc, char const *argv[])
{
    if (argc < 1) {
        std::cerr << "ERROR: no specified SDL file." << std::endl;
        exit(-1);
    }

    Scene s;
    Camera cam;
    Size size {100, 100};

    SDLReader::readSDLFile(argv[1], size, cam, s);

    std::string line;
    while (std::getline(std::cin, line)) {
        std::string path;
        std::istringstream ss(line);
        ss >> path;
        SDLReader::readCamera(ss, cam);
        pathtrace(path, size, s, cam);
    }

    return 0;
}