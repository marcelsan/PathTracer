#ifndef MESH_H
#define MESH_H

#include "object.h"
#include "material.h"
#include "intersection.h"
#include <cfloat>

using namespace glm;

namespace PathTrace {

class Mesh : public Object
{
public:
    struct Vertex {
        int v = -1, n = -1, t = -1;
    };

    struct Triangle {
        void setA(const Vertex& v);
        void setB(const Vertex& v);
        void setC(const Vertex& v);

        unsigned int a, b, c;
        int na, nb, nc;
        int ta, tb, tc;

        bool hasNormal() const;
    };

    Mesh();
    Mesh(const Material& m);
    virtual ~Mesh();
    bool intersect(const Ray& ray, Intersection& inter) const;
    vec3 samplePosition() const;
    void addVertex(vec3 vertex);
    void addTriangle(Triangle t);
    unsigned int addNormal(vec3 normal);
    void calculateNormals();

    friend std::ostream& operator<<(std::ostream &output, const Mesh& m);

private:
    std::vector<vec3> vertices;
    std::vector<Triangle> triangles;
    std::vector<vec3> normals;
};

}

#endif