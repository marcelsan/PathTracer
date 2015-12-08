#include "sdlreader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "quadric.h"
#include "camera.h"
#include "object.h"
#include "mesh.h"

namespace PathTrace {

namespace SDLReader {

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

inline static unsigned int mtoi(const std::ssub_match& m)
{
    return std::stoi(m.str()) - 1;
}

inline static Mesh::Vertex readVertex(const std::smatch& match)
{
    Mesh::Vertex v;
    v.v = mtoi(match[1]);
    if (match[2].length() == 0)
        return v;
    if (match[3].length() != 0)
        v.t = mtoi(match[3]);
    if (match[4].length() != 0)
        v.n = mtoi(match[4]);
    return v;
}

std::istream& operator>> (std::istream& stream, Mesh::Triangle& t)
{
    // TODO: add support to texture
    static std::regex vertex_regex("(\\d+)(\\/(\\d*)\\/(\\d+))?");
    std::string s;
    std::vector<unsigned int> indices;
    std::getline(stream, s);

    auto vertex_match = std::sregex_iterator(s.begin(), s.end(), vertex_regex);
    t.setA(readVertex(*vertex_match));
    t.setB(readVertex(*(++vertex_match)));
    t.setC(readVertex(*(++vertex_match)));

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

std::string dirpath(std::string filepath)
{
    std::size_t found = filepath.rfind("/");
    if (found == std::string::npos)
        exit(-1);

    filepath.erase(filepath.begin() + found + 1, filepath.end());
    return filepath;
}

inline void readOBJFile(const std::string& url, PathTrace::Mesh& mesh)
{
    if(url == "")
        return;

    // TODO: improve this part of code
    std::ifstream stream;
    load(url, stream);
    bool has_normal = true;

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
            has_normal &= t.hasNormal();
            mesh.addTriangle(t);
        }
        else if (option == "vn") {
            vec3 vn;
            ss >> vn;
            mesh.addNormal(vn);
        }
    }

    if (!has_normal)
        mesh.calculateNormals();
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

inline static void readBackground(std::istream& stream, Scene& s)
{
    color background;
    stream >> background;
    s.setBackground(background);
}

inline static void readAmbient(std::istream& stream, Scene& s)
{
    float Ia;
    stream >> Ia;
    s.Ia = Ia;
}

inline static void readLight(std::istream& stream, Scene& s)
{
    // TODO
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

inline static void readTonemapping(std::istream& stream, ImageBuffer& image)
{
    float tonemapping;
    stream >> tonemapping;
    image.setTonemapping(tonemapping);
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
        else if (option == "background") {
            readBackground(ss, s);
        }
        else if (option == "objectquadric") {
            readQuadric(ss, s);
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
        else if (option == "tonemapping") {
            readTonemapping(ss, image);
        }
        else if (option == "ambient") {
            readAmbient(ss, s);
        }
        else if (option == "light") {
            readLight(ss, s);
        }
        else if (option != "") {
            std::cerr << "[WARNING] Ignoring option " << option << std::endl;
        }
    }

    stream.close();
}

}

}
