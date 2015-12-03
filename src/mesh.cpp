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

void Mesh::addVertex(vec3 v)
{
    vertices.push_back(v);
}

void Mesh::addTriangle(Triangle t)
{
    triangles.push_back(t);
}

void Mesh::addNormal(vec3 n)
{
    normals.push_back(n);
}

void Mesh::resetObject()
{
    this->vertices.clear();
    this->triangles.clear();
    this->normals.clear();
}

std::ostream& operator<<(std::ostream &output, const Mesh& m)
{
    for (const auto& v: m.vertices) {
        output << "v "
            << v.x << " "
            << v.y << " "
            << v.z << std::endl;
    }

    for (const auto& n: m.normals) {
        output << "vn "
            << n.x << " "
            << n.y << " "
            << n.z << std::endl;
    }

    for (const auto& t : m.triangles) {
        output << "f "
            << t.a << "//"  << t.na << " "
            << t.b << "//"  << t.nb << " "
            << t.c << "//"  << t.nc << std::endl;
    }

    return output;
}

}