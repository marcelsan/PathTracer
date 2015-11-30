
#include "scene.h"

namespace PathTrace {

Scene::Scene()
{
} 

void Scene::add(std::unique_ptr<Object> o)
{
	objects.push_back(std::move(o));
}

void Scene::setCamera(const Camera &c)
{
    cam = c;
}
}