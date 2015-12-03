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

void Mesh::print()
{   

    std::cout << "aqui" << std::endl;

    for(int i = 0; i < vertices.size(); ++i)
    {
        std::cout << "v " << vertices[i].x << " " 
                  << vertices[i].y << " " 
                  << vertices[i].z << "\n";
    }

    for(int i = 0; i < normals.size(); ++i)
    {
        std::cout << "vn " << normals[i].x << " " 
                  << normals[i].y << " " 
                  << normals[i].z << "\n";
    }

    for(int i = 0; i < triangles.size(); ++i)
    {
        std::cout << "f " << triangles[i].a << "//"  << triangles[i].na << " " 
                  << triangles[i].b << "//"  << triangles[i].nb << " " 
                  << triangles[i].c << "//"  << triangles[i].nc << "\n"; 
    }
}

}