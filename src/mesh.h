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
    bool intersect(const Ray& ray, Intersection& inter) const;
    void addVertex(vec3 vertex);
    void addTriangle(Triangle t);
    void addNormal(vec3 normal);
    void resetObject();

    friend std::ostream& operator<<(std::ostream &output, const Mesh& m);

private:
    std::vector<vec3> vertices;
    std::vector<Triangle> triangles;
    std::vector<vec3> normals;
};

}

#endif