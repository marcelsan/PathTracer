#include "mesh.h"

namespace PathTrace {

Mesh::Mesh()
{

}

Mesh::Mesh(const Material& m) : Object(m)
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

void Mesh::addVertex(vec3 vertex)
{
    vertices.push_back(vertex.x);
    vertices.push_back(vertex.y);
    vertices.push_back(vertex.z);
}

void Mesh::addNormals(vec3 normal)
{
    normals.push_back(normal.x);
    normals.push_back(normal.y);
    normals.push_back(normal.z);
}

void Mesh::addTriangleIndices(int a, int b, int c)
{
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

void Mesh::resetObject()
{
    this->vertices.clear();
    this->indices.clear();
    this->normalIndices.clear();
    this->normals.clear();
}

}