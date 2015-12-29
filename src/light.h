#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "color.h"

using namespace glm;

namespace PathTrace {

class Object;

class Light
{
public:
    Light(bool d = false, Object* o = nullptr) : directional(d), obj(o) { }
    virtual ~Light() = default;

    bool directional;
    Object* object() const { return obj; }
    virtual vec3 direction() const = 0;
    virtual color emissionColor() const = 0;
    virtual vec3 samplePosition() const;

private:
    Object* obj;
};

class SingleColorLight : public Light
{
private:
    color cl;
public:
    SingleColorLight(Object* o = nullptr, color c = {})
        : Light(false, o)
        , cl(c)
    { }
    vec3 direction() const { return {}; }
    virtual ~SingleColorLight() = default;
protected:
    color emissionColor() const override { return cl; }
};

class DirectionalLight : public Light
{
public:
    DirectionalLight(vec3 d, float ip) 
        : Light(true)
        , dir(d)
        , ip(ip) { }

    vec3 dir;
    float ip;

    vec3 samplePosition() const { return {}; }
    vec3 direction() const { return dir; }
    color emissionColor() const override { return {ip * 1.0f, ip * 1.0f, ip * 1.0f}; }
};

}

#endif