#include "ray.h"

namespace PathTrace {

static std::ostream& operator<<(std::ostream& stream, const vec3& v)
{
    return stream << v.x << " " <<  v.y << " " << v.z;
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    return os << "eye: " << ray.o << " dir: " << ray.d;
}

}