
#include "camera.h"

#include <cassert>

namespace PathTrace {

Ray Camera::ray(float i, float j) const
{
    // Z always == 0
    vec2 clip = clipMax - clipMin;
    vec3 dest = vec3(clipMin.x, clipMin.y, 0) + vec3(clip.x * j, clip.y * i, 0);

    return {eye, dest - eye};
}

void Camera::setEye(const vec3& e)
{
    eye = e;
}

void Camera::setOrtho(const vec2& min, const vec2& max)
{
    clipMin = min;
    clipMax = max;
}

}