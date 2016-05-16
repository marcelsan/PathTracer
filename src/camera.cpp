
#include "camera.h"
#include <glm/gtx/transform.hpp>
#include <cmath>
#include <cassert>

namespace PathTrace {

Ray Camera::ray(float i, float j) const
{
    vec2 clip = clipMax - clipMin;
    vec3 dest = vec3(clipMin.x, clipMin.y, 0) + vec3(clip.x * j, clip.y * (1.0f - i), 0);

    dest.x = dest.x *  tan(fov / 2) * aspect;
    dest.y = dest.y *  tan(fov / 2);

    const glm::dmat4 V = glm::translate(-eye)
                     * glm::rotate(glm::radians(rot[2]), glm::vec3(0, 0, 1)) 
                     * glm::rotate(glm::radians(rot[0]), glm::vec3(1, 0, 0)) 
                     * glm::rotate(glm::radians(rot[1]), glm::vec3(0, 1, 0));

    glm::vec4 rayPWorld = glm::inverse(V) * glm::dvec4(dest.x, dest.y, -1.0, 1.0);
    glm::vec4 rayOriginWorld = glm::inverse(V) * glm::dvec4(0.0f, 0.0f, 0.0f, 1.0f);

    return {glm::vec3(rayOriginWorld), 
            glm::normalize(glm::vec3(rayPWorld) - glm::vec3(rayOriginWorld))};
}

void Camera::setAspect(float a)
{
    aspect = a;
}

void Camera::setEye(const vec3& e)
{
    eye = e;
}

void Camera::setRot(const vec3& r)
{
    rot = r;
}

void Camera::setOrtho(const vec2& min, const vec2& max)
{
    clipMin = min;
    clipMax = max;
}

void Camera::setNPaths(unsigned n)
{
    npaths = n;
}

unsigned Camera::nPaths() const
{
    return npaths;
}

}