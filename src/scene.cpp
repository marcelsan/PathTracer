#include "scene.h"

#include <glm/glm.hpp>

using namespace glm;

namespace PathTrace {

Scene::Scene()
{
}

void Scene::add(std::unique_ptr<Object> o)
{
    objects.push_back(std::move(o));
}

bool Scene::raycast(const Ray& ray, Intersection& closestInter, float& closest_distance) const
{
    bool any_intersection = false;

    for (auto const& o : objects) {
        Intersection inter;
        if (!o->intersect(ray, inter))
            continue;

        float d = distance(ray.o, inter.p);
        if (d > closest_distance)
            continue;

        closest_distance = d;
        closestInter = inter;
        closestInter.o = o.get();
        any_intersection = true;
    }

    return any_intersection;
}

void Scene::setBackground(const color& c)
{
    bg = c;
}

void Scene::addLight(std::unique_ptr<Light> l)
{
    lights.push_back(std::move(l));
}

const std::vector<std::unique_ptr<Light>>& Scene::getLights() const
{
    return lights;
}

}