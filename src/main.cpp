
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <memory>

#include "scene.h"
#include "imagebuffer.h"
#include "sdlreader.h"
#include "raytrace.h"

using namespace glm;
using namespace PathTrace;

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cerr << "ERROR: no specified SDL file." << std::endl;
        exit(-1);
    } else if (argc < 3) {
        std::cerr << "ERROR: no specified .pnm output file." << std::endl;
        exit(-1);
    }

    Scene s;
    Camera cam;
    ImageBuffer ib(100, 100);

    std::string path(argv[1]);
    SDLReader::readSDLFile(path, ib, cam, s);

    raytrace(ib, s, cam);

    std::ofstream ofs (argv[2], std::ofstream::out);
    ofs << ib;
    ofs.close();

    return 0;
}