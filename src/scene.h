#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "camera.h"
#include "color.h"
#include "object.h"

using namespace glm;

namespace PathTrace {

class Scene
{
private:
    std::vector<std::unique_ptr<Object>> objects;
    color bg;

public:
    Scene();

    void add(std::unique_ptr<Object> o);
    bool raycast(const Ray& ray, Intersection& inter) const;
    void setBackground(const color& c);
    const color& background() const { return bg; }
};

}

#endif