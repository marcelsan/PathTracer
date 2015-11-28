
#include "scene.h"

namespace PathTrace {

Scene::Scene()
{
} 

void Scene::add(std::unique_ptr<Object> o)
{
	objects.push_back(std::move(o));
}

void Scene::setEyePosition(float x, float y, float z)
{
    eyePosition.x = x;
    eyePosition.y = y;
    eyePosition.z = z;
}
}