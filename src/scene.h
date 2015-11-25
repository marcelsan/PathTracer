#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "object.h"

namespace PathTrace {

class Scene
{
private:
	std::vector<std::unique_ptr<Object>> objects;

public:
	Scene();

	void add(std::unique_ptr<Object> o);
};

}

#endif