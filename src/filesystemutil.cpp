#include "filesystemutil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
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

std::istream& operator>> (std::istream& stream, Mesh::Triangle& t)
{
    // TODO: add support to texture
    static std::regex dd("(\\d+)\\/\\/(\\d+)");
    std::string s;
    std::vector<unsigned int> indices;
    std::getline(stream, s);

    auto words_begin = std::sregex_iterator(s.begin(), s.end(), dd);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;   

        indices.push_back(std::stoi(match[1].str()) - 1);
        indices.push_back(std::stoi(match[2].str()) - 1);
    }

    t.a  = indices[0];
    t.na = indices[1];
    t.b  = indices[2];
    t.nb = indices[3];
    t.c  = indices[4];
    t.nc = indices[5];

    return stream;
} 

inline static std::istream& operator>>(std::istream& stream, vec3& v)
{
    return stream >> v.x >> v.y >> v.z;
}

inline static std::istream& operator>>(std::istream& stream, vec2& v)
{
    return stream >> v.x >> v.y;
}

inline void readOBJFile(const std::string& url, PathTrace::Mesh& mesh)
{
    if(url == "")
        return;

    // TODO: improve this part of code
    std::ifstream stream;
    load(url, stream);

    while(!stream.eof()) {
        std::string line;
        std::string option;
        std::getline(stream, line);
        std::stringstream ss(line);

        ss >> option;

        if (option[0] == '#')
            continue;

        if (option == "v") {
            vec3 v;
            ss >> v;
            mesh.addVertex(v);
        }
        else if(option[0] == 'f') {
            Mesh::Triangle t;
            ss >> t;
            mesh.addTriangle(t);
        }
        else if (option == "vn") {
            vec3 vn;
            ss >> vn;
            mesh.addNormal(vn);
        } 
    }
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
    stream >> eye;
    cam.setEye(eye);
}

inline static void readOrtho(std::istream& stream, Camera& cam)
{
    vec2 min, max;
    stream >> min >> max;
    cam.setOrtho(min, max);
}

inline static void readMesh(const std::string& path, std::istream& stream, Scene& s)
{
    std::string objFile;
    stream >> objFile;

    Material mat = readMaterial(stream);
    std::unique_ptr<Mesh> mesh(new Mesh(mat));
    readOBJFile(path + objFile, *mesh);
    s.add(std::move(mesh));
}

inline static void readSize(std::istream& stream, ImageBuffer& image)
{
    size_t w, h;
    stream >> w >> h;
    image.setSize(w, h);
}

std::string dirpath(std::string filepath)
{
    std::size_t found = filepath.rfind("/");
    if (found == std::string::npos)
        exit(-1);

    filepath.erase(filepath.begin() + found + 1, filepath.end());
    return filepath;
}

void readSDLFile(const std::string& sdlpath, ImageBuffer& image, Camera& cam, PathTrace::Scene& s)
{
    std::ifstream stream;
    load(sdlpath, stream);

    std::string path = dirpath(sdlpath);

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
        else if (option ==  "ortho") {
            readOrtho(ss, cam);
        }
        else if (option == "object") {
            readMesh(path, ss, s);
        }
        else if (option == "size") {
            readSize(ss, image);
        }
    }

    stream.close();
}

}