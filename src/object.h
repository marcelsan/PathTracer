#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <memory>

#include "aabb.h"

namespace PathTrace {

class Object {
public:
	Object();
	virtual ~Object();

	virtual AABB& aabb() const { return AABB(); }
};

}

#endif