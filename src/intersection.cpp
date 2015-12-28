#include "intersection.h"

namespace PathTrace {
Ray Intersection::rayTo(vec3 dir) const
{
	return {p + dir * 0.00000001f, dir};
}
}
