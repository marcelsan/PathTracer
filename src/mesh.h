#ifndef MESH_H
#define MESH_H

#include "object.h"

using namespace glm;

namespace PathTrace {

class Mesh : public Object
{
private:
    std::vector<float> vertices;
    std::vector<float> normals; 
    std::vector<unsigned int> indices;
    std::vector<unsigned int> normalIndices;

public:
    Mesh();
    Mesh(const Material& m);
    virtual ~Mesh();
    Intersection intersect(const Ray& ray) const;
    void addVertex(vec3 vertex);
    void addNormals(vec3 normal);
    void addTriangleIndices(int a, int b, int c);
    void resetObject();

};

}

#endif