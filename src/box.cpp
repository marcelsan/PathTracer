#include "box.h"

#include <cmath>

namespace PathTrace {

Box::Box(vec3 mn, vec3 mx)
    : Object()
    , min(mn)
    , max(mx)
{
}

Box::~Box()
{
}

bool Box::intersect(const Ray& r, Intersection& inter) const
{
    vec3 invd = {1.0f / r.d.x, 1.0f / r.d.y, 1.0f / r.d.z};

    float tx1 = (min.x - r.o.x) * invd.x;
    float tx2 = (max.x - r.o.x) * invd.x;

    float tmin = fmin(tx1, tx2);
    float tmax = fmax(tx1, tx2);

    float ty1 = (min.y - r.o.y) * invd.y;
    float ty2 = (max.y - r.o.y) * invd.y;

    tmin = fmax(tmin, fmin(ty1, ty2));
    tmax = fmin(tmax, fmax(ty1, ty2));

    float tz1 = (min.z - r.o.z) * invd.z;
    float tz2 = (max.z - r.o.z) * invd.z;

    tmin = fmax(tmin, fmin(tz1, tz2));
    tmax = fmin(tmax, fmax(tz1, tz2));

    return tmax >= tmin;
}

}