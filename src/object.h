#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <memory>

namespace PathTrace {

class Object {
public:
	Object();
	virtual ~Object();

    virtual Intersection intersect(const Ray& r) const = 0;
};

}

#endif