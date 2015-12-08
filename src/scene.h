#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "camera.h"
#include "color.h"
#include "object.h"
#include "light.h"

using namespace glm;

namespace PathTrace {

class Scene
{
private:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Light>> lights;
    color bg;
    float Ia;

public:
    Scene();

    void addLight(std::unique_ptr<Light> l);
    void setIa(float ia) { Ia = ia; }
    const std::vector<std::unique_ptr<Light>>& getLights() const;
    void add(std::unique_ptr<Object> o);
    bool raycast(const Ray& ray, Intersection& inter) const;
    void setBackground(const color& c);
    const color& background() const { return bg; }
};

}

#endif