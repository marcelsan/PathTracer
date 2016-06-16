
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "feature.h"
#include "scene.h"
#include "sdlreader.h"
#include "raytrace.h"

using namespace glm;
using namespace PathTrace;

int main(int argc, char const **argv)
{
    if (argc < 2) {
        std::cerr << "ERROR: no specified SDL file." << std::endl;
        exit(-1);
    } else if (argc < 3) {
        std::cerr << "ERROR: no specified waypoints file." << std::endl;
        exit(-1);
    } else if (argc < 4) {
        std::cerr << "ERROR: no specified output file." << std::endl;
        exit(-1);
    }

    Scene s;
    Camera cam;
    Size size {100, 100};
    SDLReader::readSDLFile(argv[1], size, cam, s);

    uint nFrames;
    std::ifstream waypointStream(argv[2], std::ifstream::in);
    waypointStream >> nFrames;

    NPYWriter writer(argv[3]);
    writer.writeHeader({nFrames, cam.nPaths(), (uint)size.height, (uint)size.width, Feature::feature_size});
    for (uint i = 0; i < nFrames; ++i) {
        std::cerr << "frame " << i << std::endl;
        SDLReader::readCamera(waypointStream, cam);
        pathtrace(writer, size, s, cam);
    }

    return 0;
}
