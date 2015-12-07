
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <memory>

#include "scene.h"
#include "imagebuffer.h"
#include "filesystemutil.h"
#include "raytrace.h"

using namespace glm;
using namespace PathTrace;

int main(int argc, char const *argv[])
{
    Scene s;
    Camera cam;
    ImageBuffer ib(100, 100);

    if (argc < 3)
        exit(-1);

    std::string path(argv[1]);
    FileSystemUtil::readSDLFile(path, cam, s);

    raytrace(ib, s, cam);

    std::ofstream ofs (argv[2], std::ofstream::out);
    ofs << ib;
    ofs.close();

    return 0;
}