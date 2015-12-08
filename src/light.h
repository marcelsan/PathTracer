#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "color.h"
#include "mesh.h"

using namespace glm;

namespace PathTrace {

class Light
{
public:
    Light() = default;
    virtual ~Light() = default;

    virtual color sampleColor(const Intersection& inter) const = 0;
};

class SingleColorLight : public Light
{
private:
    color cl;
public:
    SingleColorLight(color c = {})
        : Light()
        , cl(c)
    { }
    virtual ~SingleColorLight() = default;
protected:
    const color& emissionColor() const { return cl; }
};


class DirectionalLight : public SingleColorLight
{
private:
    vec3 dir;
public:
    DirectionalLight(vec3 direction, color c = {})
        : SingleColorLight(c)
        , dir(normalize(direction))
    { }
    virtual ~DirectionalLight() = default;

    virtual color sampleColor(const Intersection& inter) const
    {
        float intensity = dot(normalize(inter.n), dir);
        std::cout  << " --- " << intensity << std::endl;
        if (intensity <= 0.0f)
            return black;
        return emissionColor() * intensity;

    }
};

}

#endif