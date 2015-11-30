#include "filesystemutil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "camera.h"
#include "object.h"
#include "quadric.h"

using namespace PathTrace;

namespace FileSystemUtil {

inline static void load(const std::string& url, std::ifstream& stream)
{
    if (url == "")
        return;

    stream.open(url.c_str());
    if (!stream.is_open()) {
        std::cerr << "ERROR: file not loaded: " << url.c_str() << std::endl;
        exit(-1);
    }
}

inline static void readQuadric(std::istream& stream, Scene& s)
{
    float a, b, c, d, e, f, g, h, j, k;
    float red, green, blue;
    float ka, kd, ks, kt;
    int n;

    stream >> a >> b >> c >> d >> e >> f >> g >> h >> j >> k;
    stream >> red >> green >> blue;
    stream >> ka >> kd >> ks >> kt;
    stream >> n;

    Material mat(vec3(red,green,blue), ka, kd, ks, kt, n);
    s.add(std::unique_ptr<Object>(new Quadric(a,b,c,d,e,f,g,h,j,k,mat)));
}

inline static void readEye(std::istream& stream, Scene& s)
{
    float x, y, z;
    stream >> x >> y >> z;
    Camera cam(vec3(x, y , z));
    s.setCamera(cam);
}

void readSDLFile(const std::string& path, PathTrace::Scene& s)
{
    std::ifstream stream;
    load(path, stream);
    while(!stream.eof()) {
        std::string line;
        std::getline(stream, line);
        std::stringstream ss(line);

        std::string option;
        ss >> option;

        if (option[0] == '#') {
            // TODO: read until next line
            continue;
        }

        if (option == "objectquadric") {
            readQuadric(ss, s);
        } 
        else if (option == "background") {
            // TODO
        }
        else if (option ==  "eye") {
            readEye(ss, s);
        } 
    }

    stream.close();
}

}