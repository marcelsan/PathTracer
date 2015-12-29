#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "color.h"

using namespace glm;

namespace PathTrace {

class Object;

class Light
{
private:
    Object* obj;

public:
    Light(Object* o = nullptr) : obj(o) { }
    virtual ~Light() = default;

    Object* object() const { return obj; }
    virtual color emissionColor() const = 0;
    virtual vec3 samplePosition() const;
};

class SingleColorLight : public Light
{
private:
    color cl;
public:
    SingleColorLight(Object* o = nullptr, color c = {})
        : Light(o)
        , cl(c)
    { }
    virtual ~SingleColorLight() = default;
protected:
    color emissionColor() const override { return cl; }
};

class DirectionalLight : public Light
{
public:
    DirectionalLight(vec3 d, float ip) : direction(d), ip(ip) { }
    vec3 direction;
    float ip;

    vec3 samplePosition() const { return direction; };
    color emissionColor() const override { return {}; }
};

}

#endif