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

bool Mesh::intersect(const Ray& ray, Intersection& inter) const
{
    // TODO: implement intersection with mesh
    return false;
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