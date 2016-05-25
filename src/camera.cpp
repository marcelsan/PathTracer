
#include "camera.h"
#include "util.h"
#include <glm/gtx/transform.hpp>
#include <cmath>
#include <cassert>

namespace PathTrace {

Ray Camera::ray(float i, float j) const
{
    vec2 clip = clipMax - clipMin;
    vec3 dest = vec3(clipMin.x, clipMin.y, 0) + vec3(clip.x * j, clip.y * (1.0f - i), 0);
    
    glm::vec4 rayPWorld = M * glm::dvec4(dest.x, dest.y, 1.0, 1.0);
    glm::vec4 rayOriginWorld = M * glm::dvec4(0.0f, 0.0f, 0.0f, 1.0f);

    if(rayPWorld.w != 0) rayPWorld = rayPWorld / rayPWorld.w;
    if(rayOriginWorld.w != 0) rayOriginWorld = rayOriginWorld / rayOriginWorld.w;

    return {glm::vec3(rayOriginWorld), glm::normalize(glm::vec3(rayPWorld) - glm::vec3(rayOriginWorld))};
}

void Camera::apply()
{
    const glm::dmat4 P = glm::perspective(fov, aspect, float(0.01), float(1000));
    const glm::dmat4 V = glm::lookAt(eye, center, up);

    M = glm::inverse(P * V);
}

void Camera::lookAt(const vec3& e, const vec3& c, const vec3& u)
{
    eye = e;
    center = c;
    up = u;
}

void Camera::setAspect(float a)
{
    aspect = a;
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