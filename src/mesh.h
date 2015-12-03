#ifndef MESH_H
#define MESH_H

#include "object.h"

using namespace glm;

namespace PathTrace {

class Mesh : public Object
{
public:
    struct Triangle {
        unsigned int a, b, c;
        unsigned int na, nb, nc;
    };

    Mesh();
    Mesh(const Material& m);
    virtual ~Mesh();
    Intersection intersect(const Ray& ray) const;
    void addVertex(vec3 vertex);
    void addTriangle(Triangle t);
    void addNormal(vec3 normal);
    void resetObject();
    std::ostream& operator<< (std::ostream& output);

private:
    std::vector<vec3> vertices;
    std::vector<Triangle> triangles;
    std::vector<vec3> normals;
};

}

#endif