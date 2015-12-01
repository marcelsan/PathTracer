#include "filesystemutil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "quadric.h"
#include "camera.h"
#include "object.h"
#include "mesh.h"

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

inline void readOBJFile(const std::string& url, PathTrace::Mesh* m) 
{
    if(url == "")
        return;

    std::ifstream stream;
    load(url, stream);

    // ToDO: consider more general types of obj files

    while(!stream.eof()) {
        std::string line;
        std::string option;
        getline(stream, line);
        std::stringstream ss(line);

        ss >> option;

        if(option[0] == '#') {
            continue;
        }

        if (option[0] == 'v') {
            float x, y, z;
            ss >> x >> y >> z;
            m->addVertex(vec3(x, y, z));
        } else if (option[0] == 'n') {
            // TODO
        } else if(option[0] == 'f') {
            int a, b, c;
            ss >> a >> b >> c;
            m->addTriangle(a, b, c);
        }
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

inline static void readEye(std::istream& stream, Camera& cam)
{
    vec3 eye;
    stream >> cam.eye;
}

inline static void readMesh(std::istream& stream, Scene& s)
{
    std::string objFile;
    stream >> objFile;

    Material mat = readMaterial(stream);
    Mesh* m = new Mesh(mat);

    readOBJFile(objFile, m);
    s.add(std::unique_ptr<Object>(m));
}

void readSDLFile(const std::string& path, Camera& cam, PathTrace::Scene& s)
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
            readEye(ss, cam);
        }
        else if (option == "object") {
            readMesh(ss, s);
        }
    }

    stream.close();
}

}