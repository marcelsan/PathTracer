#include "mesh.h"

using namespace glm;

namespace PathTrace {

void Mesh::Triangle::setA(const Vertex& v)
{
    a = v.v;
    na = v.n;
    ta = v.t;
}

void Mesh::Triangle::setB(const Vertex& v)
{
    b = v.v;
    nb = v.n;
    tb = v.t;
}

void Mesh::Triangle::setC(const Vertex& v)
{
    c = v.v;
    nc = v.n;
    tc = v.t;
}

bool Mesh::Triangle::hasNormal() const
{
    return (na != -1) && (nb != -1) && (nc != -1);
}

Mesh::Mesh()
    : Object()
{

}

Mesh::Mesh(const Material& m)
    : Object(m)
{
}

Mesh::~Mesh()
{
}

bool Mesh::intersect(const Ray& ray, Intersection& inter) const
{
    float closest_distance = FLT_MAX;
    bool any_intersection = false;
    
    for (const auto& tr : triangles) {
        float r, a, b;
        glm::vec3 u = vertices[tr.b] - vertices[tr.a];
        glm::vec3 v = vertices[tr.c] - vertices[tr.a];
        glm::vec3 n = glm::cross(u, v);

        glm::vec3 dir = ray.d;             
        glm::vec3 w0  = ray.o - vertices[tr.a];
        a = -glm::dot(n, w0);
        b = glm::dot(n, dir);

        if (fabs(b) < 0.00000001) 
            continue;              

        r = a / b;
        if (r < 0.0)                    
            continue;                   
        
        glm::vec3 i = ray.o + r * dir; // ponto de intersecao

        float uu, uv, vv, wu, wv, D;
        uu = glm::dot(u,u);
        uv = glm::dot(u,v);
        vv = glm::dot(v,v);
        glm::vec3 w = i - vertices[tr.a];
        wu = dot(w,u);
        wv = dot(w,v);
        D = uv * uv - uu * vv;

        float s, t;
        s = (uv * wv - vv * wu) / D;
        if (s < 0.0 || s > 1.0)         
            continue;
        
        t = (uv * wu - uu * wv) / D;     
        if (t < 0.0 || (s + t) > 1.0)
            continue;

        float d = glm::distance(i, ray.o);
        if(d > closest_distance) 
            continue;

        closest_distance = d;
        any_intersection = true;

        inter.n = glm::normalize(
                    (1 - s - t) * normals[tr.na] + 
                    s * normals[tr.nb] + 
                    t * normals[tr.nc]);

        inter.p = i;
        inter.m = material();
    }

    return any_intersection;
}

vec3 Mesh::samplePosition() const
{
    return vertices[0]; // XXX
}

void Mesh::addVertex(vec3 v)
{
    vertices.push_back(v);
}

void Mesh::addTriangle(Triangle t)
{
    triangles.push_back(t);
}

unsigned int Mesh::addNormal(vec3 n)
{
    normals.push_back(n);
    return normals.size() - 1;
}

void Mesh::calculateNormals()
{
    for (auto& t : triangles) {
        vec3 ab = vertices[t.b] - vertices[t.a];
        vec3 ac = vertices[t.c] - vertices[t.a];
        unsigned int n = addNormal(cross(ab, ac));
        t.na = t.nb = t.nc = n;
    }
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