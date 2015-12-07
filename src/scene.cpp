
#include "scene.h"

#include <glm/glm.hpp>
#include <limits>

using namespace glm;

namespace PathTrace {

Scene::Scene()
{
}

void Scene::add(std::unique_ptr<Object> o)
{
    objects.push_back(std::move(o));
}

bool Scene::raycast(const Ray& ray, Intersection& closestInter) const
{
    float closest_distance =  std::numeric_limits<float>::max();
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
        any_intersection = true;
    }

    return any_intersection;
}

}