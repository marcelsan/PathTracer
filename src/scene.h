#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "object.h"

using namespace glm;

namespace PathTrace {

class Scene
{
private:
	std::vector<std::unique_ptr<Object>> objects;
    vec3 eyePosition;

public:
	Scene();

	void add(std::unique_ptr<Object> o);
    void setEyePosition(float x, float y, float z);
};

}

#endif