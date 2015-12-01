
#include "camera.h"

#include <cassert>

namespace PathTrace {

Ray Camera::ray(const vec2& param) const
{
    assert(0 <= param.x && param.x <= 1);
    assert(0 <= param.y && param.y <= 1);

    vec2 c = param - vec2(0.5f, 0.5f);

    Ray r;
    r.o = focus + c.x * vx + c.y * vy;
    r.d = r.o - eye;
    return r;
}

void Camera::setEye(const vec3& e)
{
    eye = e;
    updateVxVy();
}

void Camera::setDir(const vec3& d)
{
    dir = d;
    updateVxVy();
}

void Camera::setUp(const vec3& u)
{
    up = u;
    updateVxVy();
}

void Camera::updateVxVy()
{
    // TODO: create a matrix for this
    vec2 clip = clipMax - clipMin;

    vx = normalize(cross(dir, up)) * clip.x;
    vy = normalize(-up) * clip.y;
    focus = eye + normalize(dir) * focusDistance;
}

}