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

inline static std::istream& operator>>(std::istream& stream, vec3& v)
{
    return stream >> v.x >> v.y >> v.z;
}

inline static Material readMaterial(std::istream& stream)
{
    vec3 color;
    float ka, kd, ks, kt;
    int n;

    stream >> color;
    stream >> ka >> kd >> ks >> kt;
    stream >> n;

    return Material(color, ka, kd, ks, kt, n);
}

inline static void readQuadric(std::istream& stream, Scene& s)
{
    float a, b, c, d, e, f, g, h, j, k;
    stream >> a >> b >> c >> d >> e >> f >> g >> h >> j >> k;
    Material mat = readMaterial(stream);
    s.add(std::unique_ptr<Object>(new Quadric(a,b,c,d,e,f,g,h,j,k,mat)));
}

inline static void readEye(std::istream& stream, Scene& s)
{
    vec3 eye;
    stream >> eye;
    Camera cam(eye);
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