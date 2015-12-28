#include "intersection.h"

namespace PathTrace {
Ray Intersection::rayTo(vec3 dir) const
{
	return {p + n * 0.000001f, dir};
}
}
