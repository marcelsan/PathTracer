#ifndef MESH_H
#define MESH_H

#include "object.h"

using namespace glm;

namespace PathTrace {

class Mesh : public Object
{
    struct Triangle {
        unsigned int a, b, c;
    };

    struct Vertex {
        vec3 pos, normal;
    };

private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

public:
    Mesh();
    Mesh(const Material& m);
    virtual ~Mesh();
    Intersection intersect(const Ray& ray) const;
    void addVertex(vec3 vertex, vec3 normal = {});
    void addTriangle(unsigned int a, unsigned int b, unsigned int c);
    void resetObject();

};

}

#endif