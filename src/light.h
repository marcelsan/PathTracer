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
    Light(bool d = false, float ip = 1.0f, Object* o = nullptr) : directional(d), ip(ip), obj(o) { }
    virtual ~Light() = default;

    bool directional;
    float ip;
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
    SingleColorLight(Object* o = nullptr, color c = {}, float ip = 1.0f)
        : Light(false, ip, o)
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
        : Light(true, ip)
        , dir(d)
    { }

    vec3 dir;

    vec3 samplePosition() const { return {}; }
    vec3 direction() const { return dir; }
    color emissionColor() const override { return {ip * 1.0f, ip * 1.0f, ip * 1.0f}; }
};

}

#endif