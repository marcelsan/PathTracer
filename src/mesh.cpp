#include "mesh.h"

namespace PathTrace {

Mesh::Mesh()
{

}

Mesh::Mesh(const Material& m)
    : Object(m)
{

};

Mesh::~Mesh()
{

}

Intersection Mesh::intersect(const Ray& ray) const
{
    // ToDO: implement intersection with mesh

    return {};
}

void Mesh::addVertex(vec3 vertex, vec3 normal)
{
    Vertex v = {vertex, normal};
    vertices.push_back(v);
}

void Mesh::addTriangle(unsigned int a, unsigned int b, unsigned int c)
{
    triangles.push_back({a, b, c});
}

void Mesh::resetObject()
{
    this->vertices.clear();
    this->triangles.clear();
}

}