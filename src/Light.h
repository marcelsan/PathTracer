#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <iostream>
#include "Vec.h"

class Light
{
private:
	Vec3f dir;
	double intensity;

public:
	Light () {}

	Light (Vec3f dir, double intensity) : dir(dir), intensity(intensity) {}

	Vec3f getDirection() const
	{
		return dir;
	}

	float getIntensity() const
	{
		return intensity
	}
};
#endif